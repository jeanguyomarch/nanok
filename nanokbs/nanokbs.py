#! /usr/bin/env python3

import argparse
import os
import re
import sys

import hjson
import jinja2

THIS_DIR = os.path.dirname(os.path.realpath(__file__))
NANOK_DIR = os.path.abspath(os.path.join(THIS_DIR, os.pardir))

class Help:
    APP = "Path to the (relaxed) JSON file that describes the NanoK Application"
    TEMPLATE = "Path to the build system template file"
    OUTPUT = "Path where to store the templated build system"

def getopts(argv):
    parser = argparse.ArgumentParser(description='NanoK build system generator')
    parser.add_argument('--app', '-a', metavar='APP.hjson',
                        required=True, help=Help.APP)
    parser.add_argument('--template', '-t', metavar='BUILD.j2',
                        required=True, help=Help.TEMPLATE)
    parser.add_argument('--output', '-o', metavar='OUTPUT',
                        help=Help.OUTPUT)
    return parser.parse_args(argv[1:])

def canon(path):
    for elt in ("\\", "/", "-"):
        path = path.replace(elt, "_")
    return path

def template_nanokbs(config, db, output):
    search_paths = [
        os.path.join(THIS_DIR, "templates"),
        os.path.dirname(config),
    ]

    j2_env = jinja2.Environment(
        loader=jinja2.FileSystemLoader(search_paths),
        undefined=jinja2.StrictUndefined,
        extensions=['jinja2.ext.do']
    )
    j2_env.filters['canon'] = canon
    template = j2_env.get_template(os.path.basename(config))

    result = template.render(db)
    if output is not None:
        with open(output, 'w') as stream:
            stream.write(result)
    else:
        print(result)


# These are the keys that allow to define source files (any language)
SOURCES_KEYS = ("c_sources", "asm_sources")

def fixup_module(module):
    # List of all the sources defined within a module
    all_sources = []

    # Get the path that includes all the sources
    mod_path = module["path"]

    # By default, modules are not thrid-parties
    if "third_party" not in module:
        module["third_party"] = False

    # If a module does not define all the source keys, let define them
    # implicitely to an empty list. This allows better iteration over sources
    # by the templating engine.
    for source_key in SOURCES_KEYS:
        if not source_key in module:
            module[source_key] = ()
        else:
            # Prefix all the sources by their path
            sources = [os.path.join(mod_path, x) for x in module[source_key]]
            module[source_key] = sources
            # We use this iteration to collect all the defined sources
            all_sources.extend(sources)

    module["sources"] = all_sources


def main(argv):
    args = getopts(argv)

    # Load the nanok configuration file
    nanok_file = os.path.join(THIS_DIR, "nanok.hjson")
    with open(nanok_file, 'r') as stream:
        nanok_db = hjson.load(stream)

    # Load the app configuration file
    with open(args.app, 'r') as stream:
        app_db = hjson.load(stream)
    # Easy access to the "app" key of the app configuration
    app = app_db["app"]

    # Collect the nanok modules implicitely requested by the app (based on the
    # architecture criterion)
    app_arch = app["arch"]
    keep_modules = []
    nanok_modules = nanok_db["modules"]
    for nanok_module in nanok_modules:
        module_arch = nanok_module["arch"]
        if re.match(module_arch, app_arch):
            # Keep this module! but first, let's improve the data model
            fixup_module(nanok_module)
            keep_modules.append(nanok_module)

    # Set only the modules we need to compile
    nanok_db["modules"] = keep_modules

    all_sources_by_lang = {}
    for key in SOURCES_KEYS:
        all_sources_by_lang[key] = []
    for module in keep_modules:
        for key in SOURCES_KEYS:
            all_sources_by_lang[key].extend(module[key])

    for key, sources in all_sources_by_lang.items():
        nanok_db[key] = sources

    # Collect all the sources among all the modules
    all_sources = []
    for module in keep_modules:
        all_sources.extend(module["sources"])
    nanok_db["sources"] = all_sources
    nanok_db["dir"] = NANOK_DIR


    if not "products" in app:
        app["products"] = ()
    for product in app["products"]:
        fixup_module(product)


    db = {
        "nanok": nanok_db,
        "app": app,
    }

    template_nanokbs(args.template, db, args.output)

if __name__ == "__main__":
    main(sys.argv)
