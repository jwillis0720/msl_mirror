msl_mirror
==========

MSL Library Mirror

###To build external libraries required by MSL

Can follow [wiki](http://msl-libraries.org/index.php/Tutorial:Getting_started:_Compiling_MSL_with_external_libraries) 

*or* 

Run `perl buildMslEnv.pl`

This will output what you should put in your .bashrc or .tcshrc i.e.

```
export MSL_EXTERNAL_LIB_DIR=mymsl/extlib_ibs
export MSL_EXTERNAL_INCLUDE_DIR=mymsl/extlib_incs
export MSL_GSL=T
export MSL_GLPK=T
export MSL_R=F
export MSL_BOOST=T
```

###To build MSL programs
```
make bin all
```
Uses the make script and enviromental variables you set in .bashrc. 

