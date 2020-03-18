#!/usr/bin/env python
# -----------------------------------------------------------------
# struct2dot.py
#
# Create a DOT graph of struct dependencies
#
# Usage:
#   struct2dot { <cpp_directive> } <headerfile>
#
# <cpp_directive>: any 'cpp' directive but most useful is e.g.
#                  "-I <directory>" to ensure cpp finds files.
#
# <headerfile>: file with structs that you want a graph for
#
# Simplistically adapted from pycparser example: func_defs.py
# and on the cgreen-mocker in https://github.com/cgreen-devs/cgreen
#
# Since it uses pycparser it will only handle C functions and you will
# probably need the pycparsers "fake_libc_include" to avoid parsing
# the whole world of libc headers. To use it, make a soft link with
# the name 'pycparser' in the directory you are running this from, or
# in the directory of this script, to the top directory of the
# pycparser source, and cgreen-mocker will pick it up
# automatically. Or you can point to the actual fake_lib directory in
# a pycparser distribution using a command line 'cpp_directive' arg.
#
# Thanks to @gardenia for the pointer to pycparser!
#
#    https://github.com/eliben/pycparser
#
# (C) 2020, Thomas Nilefalk
#
# Using pycparser for printing out all the functions defined in a
# C file.
#
# PyCParser - Copyright (C) 2008-2015, Eli Bendersky
# License: BSD
# -----------------------------------------------------------------
from __future__ import print_function
from pycparser.plyparser import ParseError
from pycparser import c_parser, c_ast, parse_file, c_generator
from functools import reduce
import sys
import os

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])


def node2dot(node):
    if isinstance(node.type, c_ast.TypeDecl) and isinstance(node.type.type, c_ast.Struct):
        if node.coord.file == sys.argv[-1]:
            print("   ", node.type.type.name, "[style=filled,color=red]")
        print("   ", node.type.type.name, "-> {", end="")
        if node.type.type.decls:  # has fields?
            for field in node.type.type.decls:
                if isstruct(field.type):
                    print("", struct_name_of(field.type), end="")
        print(" }")


def struct_name_of(node):
    if isinstance(node, c_ast.Struct):
        return node.name
    elif isinstance(node, c_ast.TypeDecl) or isinstance(node, c_ast.PtrDecl):
        return struct_name_of(node.type)


def isstruct(node):
    if isinstance(node, c_ast.Struct):
        return True
    elif isinstance(node, c_ast.TypeDecl) or isinstance(node, c_ast.PtrDecl):
        return isstruct(node.type)


def struct2dot(args):
    # Note that cpp is used. Provide a path to your own cpp or
    # make sure one exists in PATH.

    pycparser_path = None
    # Try to find a fake_libc
    # In current directory?
    if verbose:
        print("Looking for fake_lib in current directory...")
    if os.path.isdir('pycparser'):
        pycparser_path = r'./pycparser'
    else:
        # In the directory of this script?
        path = os.path.abspath(__file__)
        if verbose:
            print(
                "Looking for fake_lib in directory of script ({0}...".format(path))
        if os.path.isdir(os.path.dirname(os.path.join(os.path.abspath(__file__),
                                                      'pycparser'))):
            pycparser_path = os.path.dirname(os.path.join(os.path.abspath(__file__),
                                                          'pycparser'))

    if pycparser_path:
        pycparser_lib = reduce(
            os.path.join, [pycparser_path, 'utils', 'fake_libc_include'])
    elif verbose:
        print("Not found")

    try:
        options = [
            '-I'+pycparser_lib] if pycparser_path else []
        if add_gnuisms:
            # And add some common GNUisms
            options = options + [
                r'-D__gnuc_va_list(c)=',
                r'-D__attribute__(x)=',
                r'-D__extension__=',
                r'-D__restrict=',
                r'-D__inline='
            ]
        if verbose:
            print("Parsing with options = {0}".format(options))
        cpp_args = list(filter(None, options))
        ast = parse_file(args[-1], use_cpp=True,
                         cpp_args=cpp_args + args[0:-1])
    except ParseError as e:
        print("ERROR: {} - C99 parse error".format(e))
        return

    print("digraph {")
    for node in (node for node in ast.ext if isinstance(node, c_ast.Typedef)):
        if isinstance(node.type.type, c_ast.Struct):
            node2dot(node)
    print("}")


def usage():
    print("""
Usage:
    struct2dot.py { <cpp_directive> } <headerfile>

    <cpp_directive>: any 'cpp' directive but most useful are e.g.
                     "-I <directory>" to ensure cpp finds files and
                     "-D <define>" to create an inline define

    <headerfile>:    file with structs to create structs to graph

    struct2dot takes a header file and generates a DOT graph for the
    relation between any struct's in it and other structs.

    If struct2dot encounters parse errors and they look like
    gnu-isms you should get a copy of the source for pycparser (on
    which cgreen-mocker is built). In it you will find a
    'fake_libc_include' which help. Create a symbolic link named
    'pycparser' that links to the root of pycparser source and
    cgreen-mocker will find it itself.

    You can find pycparser at https://github.com/eliben/pycparser

""")


if __name__ == "__main__":
    if len(sys.argv) <= 1:
        usage()
        exit(-1)
    if '-v' in sys.argv:
        verbose = True
        sys.argv.remove('-v')
    else:
        verbose = False
    if '-gnu' in sys.argv:
        add_gnuisms = True
        sys.argv.remove('-gnu')
    else:
        add_gnuisms = False
    struct2dot(sys.argv[1:])
