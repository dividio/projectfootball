# run this script from the root directory to re-generate the .pot file
#
# ./data/i18n/update_pot.sh

CPP_FILE_LIST=`find ./src -name '*.cpp' -print`

echo "--------------------"
echo "    Source Files :"
echo "--------------------"
echo $CPP_FILE_LIST


echo "---------------------------"
echo "    Generating .pot file..."
xgettext    -d projectfootball -s --keyword=_ -p ./data/i18n -o projectfootball.pot $CPP_FILE_LIST
echo "    Done"
echo "---------------------------"