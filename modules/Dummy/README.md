# Dummy Module #

The goal of this module is to offer some test and demo functions. It should
**never** be used in production.

## Configuration ##

Before using the dummy plugin, it must be loaded. This can be achieved by
adding a *load* directive to the *plugin* section of the configuration file.

For the moment, dummy offer only an "Hello World" page. To show this page, a
route must also be added to the configuration file.

```
[plugins]
    load=dummy.so

[route]
    hello=Dummy:hello
```
