./find_FILL_only_names.sh > used_FILLs.txt
../utils/struct2dot.py proto.h -colour-file used_FILLS.txt | grep -v bb_
