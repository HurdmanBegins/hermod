# Files Module #

This module allow to send files from local filesystem. The file content is
read as string so, only plain text files should be used (removing this limit
is into ToDo list)

## Configuration ##

Before using the files plugin, it must be loaded. This can be achieved by
adding a *load* directive to the *plugin* section of the configuration file.

To avoid security issues, module only get files from a directory specified
into config. A *root* directive must be added into module-specific section
of config file.

Then, to use it, at least one route must be added. The target of this
route(s) should be the page *file* of the module *Files* (Files:file).

```
[plugins]
    load=files.so

[route]
    tmp_file=Files:file

[mod:Files]
    root=/tmp
```
