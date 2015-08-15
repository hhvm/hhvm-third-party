#!/usr/bin/awk -f
#
# $Id: mk_eaw_tbl.awk 507 2011-07-16 04:25:20Z hirokawa $
#
# Description: a script to generate east asian width table.
#

# We pull in strtonum from the mingw install so that we can
# run under the version of awk included in msysgit.

# This function is under the following license:
# Arnold Robbins, arnold@skeeve.com, Public Domain
# February, 2004
function strtonum(str, ret, chars, n, i, k, c)
{
    if (str ~ /^0[0-7]*$/) {
        # octal
        n = length(str)
        ret = 0
        for (i = 1; i <= n; i++) {
            c = substr(str, i, 1)
            if ((k = index("01234567", c)) > 0)
                k-- # adjust for 1-basing in awk

            ret = ret * 8 + k
        }
    } else if (str ~ /^0[xX][0-9a-fA-f]+/) {
        # hexadecimal
        str = substr(str, 3)    # lop off leading 0x
        n = length(str)
        ret = 0
        for (i = 1; i <= n; i++) {
            c = substr(str, i, 1)
            c = tolower(c)
            if ((k = index("0123456789", c)) > 0)
                k-- # adjust for 1-basing in awk
            else if ((k = index("abcdef", c)) > 0)
                k += 9

            ret = ret * 16 + k
        }
    } else if (str ~ /^[-+]?([0-9]+([.][0-9]*([Ee][0-9]+)?)?|([.][0-9]+([Ee][-+]?[0-9]+)?))$/) {
        # decimal number, possibly floating point
        ret = str + 0
    } else
        ret = "NOT-A-NUMBER"

    return ret
}

BEGIN {
	prev = -1
	comma = 0
	ORS = ""
	FS = "[;.|# ]"
	print "static const struct {\n\tint begin;\n\tint end;\n} " TABLE_NAME "[] = {\n\t"
}

/^#/ {
}

/^[0-9a-fA-F]+;/ {
	if ($2 == "W" || $2 == "F") {

		v = strtonum( "0x" $1 )
		if (prev < 0) {
			first = v
		} else if (v - prev > 1) {
			if (comma) {
				print ",\n\t"
			}
			printf("{ 0x%04x, 0x%04x }", first, prev)
			first = v
			comma = 1
		}
		prev = v
	} else {
		if (prev >= 0) {
			if (comma) {
				print ",\n\t"
			}
			printf("{ 0x%04x, 0x%04x }", first, prev)
			prev = -1
			comma = 1
		}
	}
}

/^[0-9a-fA-F]+\.\./ {
	if ($4 == "W" || $4 == "F") {
		vs = strtonum( "0x" $1 )
		ve = strtonum( "0x" $3 )
		if (prev < 0) {
			first = vs
		} else if (vs - prev > 1) {
			if (comma) {
				print ",\n\t"
			}
			printf("{ 0x%04x, 0x%04x }", first, prev)
			first = vs
			comma = 1
		}
		prev = ve
	} else {
		if (prev >= 0) {
			if (comma) {
				print ",\n\t"
			}
			printf("{ 0x%04x, 0x%04x }", first, prev)
			prev = -1
			comma = 1
		}
	}
}

END {
	if (prev >= 0) {
		if (comma) {
			print ",\n\t"
		}
		printf("{ 0x%04x, 0x%04x }", first, prev)
	}
	print "\n};\n"
} 
