# PgConf-Generator
Generates PostgreSQL config parameter onthe fly based on the system resources.

Pre-requestites.
Ensure to have the below packages installed before building the package.
* gcc
* cc
* make

Steps to compile
* clone the repository using the git repo url.
* cd PgConf-Generator
* make

Usage of this tool
* Usage: ./pg_config_generator --generate-config-file [--read-custom-config 'specify the custom.config']
* tool can genenrate postgresql.conf when you have the custom.conf file in the directory empty or just create it.
* tool will not override the parameters that are mentioned in the custom.conf file.
* Successful run:
    * postgresql.conf is generated in same directory where you are running the program.
* Failure run:
    * postgresql.conf will not be generated.
    * fails when user permission is denied to read custom.conf file
    * fails when user permission is denied to write a new postgresql.conf file.
* Ensure the linux user permission before running the program.

Note:
* specify all the postgres parameters and its value that needs to be retained. remaning parameters will be calculated based on the host os that runs postgres.
* parameters will be calculated based on the resource allocation that postgres is hosted on.
* In case of requirement to generate a fresh postgresql.conf file. leave the custom.conf file empty and that should list all the parameter that needs to be generated.
* Ensure to note down all the parameters that needs to retained specific to environment.
* Tool will calculate only the parameters that are resource oriented.
