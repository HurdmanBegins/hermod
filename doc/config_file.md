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

* **path_session** This key is used to set the directory where session files
  are saved.
* **log_file** This key allow to specify a file name for log messages. This
  value should include the full path (like /var/log/hermod.cfg)

### Section plugins

### Section route
