#requires(if(linux:!android)|if(win32:!winphone:!wince:!winrt)|osx)

load(configure)

# FIXME: This causes tests to be installed (if examples are installed as well),
# which is needed to run some tests because they are broken.
CONFIG += ordered

load(qt_parts)
