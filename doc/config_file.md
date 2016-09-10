Main configuration file
=======================

Hermod is an application server designed to be highly modular and
customizable. There is one main configuration file used by the server itself,
and optional other files used by modules. The goal of this document is to
explain the configuration directives, and in more general how to configure
the program.

Introduction
------------

The main configuration file is named *main.cfg*. The path where this file is
searched is etc/hermod/ of installation directory. So, by default the full
name is /usr/local/etc/hermod/main.cfg .

It is always possible to define the configuration file on startup with
argument -c (file_name)

### File structure

The configuration file is inspired by INI file structure. It contains parameters
that are written as key-value pair separated by equal ("=") char. One line can
hold only one parameter. Spaces and tabs at the begining of the line are not 
significant. When the first significant char is sharp (or hashtag) the line
is considered as comment and the content is ignored.

Parameters should be inserted into sections. A section is a named group mainly 
used to bring order into the file.

Here, an example of the described structure (not a real config file) :
```
[section]
  key=value
  key2=valueA

# This is a comment
[OtherSection]
  key=valueZ
  big_key_name=some_value
```

### Real example

```
[global]
    path_session=/tmp/
    log_file=/var/log/hermod.log
[plugins]
    load=dummy.so
    load=files.so
[route]
    hello=Dummy:hello
    tmp_file=Files:file
[mod:Files]
    root=/tmp
```

Detailled description
---------------------

### Section global

* **daemon** This parameter is used to specify if hermod run in background
  (as a daemon) or not. A boolean value should be set (on/off or yes/no).
  The default value is "on".
* **log_file** This key allow to specify a file name for log messages. This
  value should include the full path (like /var/log/hermod.cfg)
* **path_session** This key is used to set the directory where session files
  are saved.
* **port** This parameter define the port number for the FCgi server socket.

### Section plugins

* **directory** This parameter set the base directory where hermod will
  search plugins.
* **load** This parameter add a file name to this list of plugins. This is a
  single value parameter, one "load" must be used for each plugin.

### Section route

The route section is a bit specific. There is no defined names for keys,
because keys are based of the target application URI. Each key/value into
the route section is an atomic route for one URI, to one module.

The key name is the URI itself. For example, if you want to use files module
to handle URL that start with /the_path/ (http://site.url/the_path/) you need
a key named "the_path".

The value for a route key, contains : the name of the module that can handle
requests, a ':', and the name of the page into this module. For example, the
page "file" of the "Files" module is "Files:file"

```
[route]
    the_path=Files:file
```

### Section for modules

Some modules may need configuration keys. To reduce the risk of name
collision, a global convention is used. All module-specific keys are located
into a deditacted section. The name of one of this sections is "mod:" and
the module name. For example, configuration keys for "files" module is named
"mod:Files".
