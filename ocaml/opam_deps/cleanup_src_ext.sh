set -e
SRC_EXT=$1
# opam does not gitignore .download but does gitignore .stamp
rm "${SRC_EXT}"/{extlib,re,cmdliner,graph,cudf,dose,uutf,jsonm}.download