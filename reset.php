<?php
    require_once("credentials.php");
    $db = new mysqli($sqlhost, $sqluser, $sqlpass, $sqldbname);
    if ($db->connect_errno) {
        die("Failed to connect to MySQL: (" . $db->connect_errno . ") " . $db->connect_error);
    }
    //unprepared query: drop all tables
    if (!$db->query(
            "DECLARE @sql NVARCHAR(max)=''
die("SYSTEM RESET IS CURRENTLY DISABLED.");

            SELECT @sql += ' Drop table ' + QUOTENAME(TABLE_SCHEMA) + '.'+ QUOTENAME(TABLE_NAME) + '; '
            FROM   INFORMATION_SCHEMA.TABLES
            WHERE  TABLE_TYPE = 'BASE TABLE'
            
            Exec Sp_executesql @sql"
        )
	) {
		die("reset tables failed: (" . $db->errno . ") " . $db->error);
    }
    echo "RESET SUCCESSFUL";
?>