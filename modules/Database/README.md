# Database module #

The goal of this module is to offer an abstraction layer to use database
with hermod. An external library is used for object relational mapping (ODB).
The current version only use Postgresql database (the only reason for that
is to redure development time), other DBMS will be added in the future.

## Configuration ##

Before using database plugin, it must be loaded. Hermod use an immediate linking
 (relocation on load) so, the loading order into config file is important !
Database must appear into *plugin* section before all other plugins that will
use it.

```
[plugins]
    load=database.so

[mod:database]
    name=hermod
    username=the_hermod_db_user
    password=some_secret_string
```
