define(`confEBINDIR',`%%PREFIX%%/libexec')
define(`confMANROOT',`%%PREFIX%%/man/man')
define(`confMANROOTMAN',`%%PREFIX%%/man/man')
define(`confUBINDIR',`%%PREFIX%%/bin')
define(`confINCLUDEDIR',`%%PREFIX%%/include')
define(`confLIBDIR',`%%PREFIX%%/lib')
define(`confSHAREDLIBDIR',`%%PREFIX%%/lib')
define(`confDONT_INSTALL_CATMAN',`True')
APPENDDEF(`confLIBDIRS', `-L%%OPENSSLLIB%% ')
APPENDDEF(`confINCDIRS', `-I%%OPENSSLINC%% ')
dnl define(`confOPTIMIZE', `-g')
