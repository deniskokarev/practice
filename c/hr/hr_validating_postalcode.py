#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/validating-postalcode
#
regex_integer_in_range = r"^[1-9]\d{5}$"
regex_alternating_repetitive_digit_pair = r"(?=(0.0|1.1|2.2|3.3|4.4|5.5|6.6|7.7|8.8|9.9))"

import re
P = raw_input()

print (bool(re.match(regex_integer_in_range, P)) 
and len(re.findall(regex_alternating_repetitive_digit_pair, P)) < 2)
