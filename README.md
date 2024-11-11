# PgConf-Generator
Generates PostgreSQL config parameter onthe fly based on the system resources.

Steps to compile
* clone the repository using the git repo url.
* cd PgConf-Generator
* make

Usage of this tool
* Usage: ./pg_config_generator --generate-config-file [--read-custom-config 'specify the custom.config']

* tool can genenrate postgresql.conf when you have the custom.conf file in the directory empty or just create it.
* tool will not override the parameters that are mentioned in the custom.conf file.
