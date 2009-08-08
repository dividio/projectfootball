# run this script from the root directory to re-generate the .pot file
#
# ./data/i18n/update_pot.sh

echo "----------------------------------"
echo "    Extracting database strings..."
echo "----------------------------------"

sqlite3 temp.sql3 < ./data/database/scripts/singleplayer/tables.sql
sqlite3 temp.sql3 < ./data/database/scripts/singleplayer/inserts_competitions.sql
sqlite3 temp.sql3 < ./data/database/scripts/singleplayer/inserts_countries.sql

sqlite3 temp.sql3 'select s_country from pf_countries' | gawk '{printf "\ngettext(\"%s\");",$0}' > ./data/i18n/temp.cpp
sqlite3 temp.sql3 'select s_short_name from pf_countries' | gawk '{printf "\ngettext(\"%s\");",$0}' >> ./data/i18n/temp.cpp
sqlite3 temp.sql3 'select s_capital from pf_countries' | gawk '{printf "\ngettext(\"%s\");",$0}' >> ./data/i18n/temp.cpp
sqlite3 temp.sql3 'select s_confederation from pf_confederations' | gawk '{printf "\ngettext(\"%s\");",$0}' >> ./data/i18n/temp.cpp

CPP_FILE_LIST=`find ./src -name '*.cpp' -print`
CPP_FILE_LIST=$CPP_FILE_LIST\ ./data/i18n/temp.cpp

echo "--------------------"
echo "    Source Files :"
echo "--------------------"
echo $CPP_FILE_LIST


echo "---------------------------"
echo "    Generating .pot file..."
echo "---------------------------"

xgettext -d projectfootball --from-code=UTF-8 -s --keyword=_ -p ./data/i18n -o projectfootball.pot $CPP_FILE_LIST

echo "---------------------------"
echo "    Removing tmp files..."
echo "---------------------------"

rm temp.sql3
rm ./data/i18n/temp.cpp

echo "---------------------------"
echo "    Done"
echo "---------------------------"
