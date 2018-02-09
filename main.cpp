#include <stdio.h>
#include <MySQLClass.h>

int main(int argc, char **argv)
{
	MySQLClass mysql("localhost", "root", "", "GameData");
    mysql.isConnected();
    mysql.loadTable("Room");
    //mysql.viewTable("Room");
	return 0;
}
