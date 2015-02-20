<?php
require_once 'util.inc';

class db 
{	
	//properties
	public $connectionID;
	
	//method to open db connection
	public function openConn()
	{
		/*connection info for perfdb site*/
		$DBName = "PerfDb";
		$DBUser = "pdb_app";
		$DBPass = "Cluster2";
		$DBHost = "localhost";
	
        $link = mysql_connect ( $DBHost, $DBUser, $DBPass ) or die ( "Could not connect<br><br>" );
		
        mysql_select_db ( $DBName ) or die ( "Could not select database<br><br>" );
		
		$this->connectionID = $link;
	}
	
	//method to close db connection
	public function closeConn()
	{
		mysql_close($this->connectionID);
	}
	
	public function run($sql)
	{
		$this->openConn();
		//$sql = stripslashes($sql);
		//$sql = addslashes($sql);
		if(substr($sql, 0, 6) == "SELECT")
		{
			$result = mysql_query($sql); //or die(/*util::logProblem('SQL Error - '.mysql_error($this->connectionID */"did not work")));
			return($result);
		} else {
			if(!mysql_query($sql)){
				//util::logProblem('SQL Error - '.mysql_error($this->connectionID));
				//util::error("There was an error inserting your information into the database. Please try again or contact the administrator for assistance." . util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			}
		}
		$this->closeConn();
	}
	
	public function runTx($arrSql)
	{
		$result = false;
		if (count($arrSql) > 0){
			$this->openConn();
			mysql_query('START TRANSACTION');
			foreach($arrSql as $sql){
				mysql_query($sql);
			}
			if (mysql_error($this->connectionID)){
				mysql_query('ROLLBACK');				
			}else{
				mysql_query('COMMIT');
				$result = 'commit';
			}
			$this->closeConn();
		}
		return $result;
	}
	
	public function runDebug($sql)
	{
		$this->openConn();
		if(substr($sql, 0, 6) == "SELECT")
		{
			echo "<p>Running Select:<p>";
			echo ($sql.' - '.mysql_error($this->connectionID)."<br>");
			$result = mysql_query($sql) or die(util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			
			return($result);
		} else {
			if(mysql_query($sql)){
				echo "<p>Running Query:<p>";
				echo ($sql);
				util::alert ("Query Ran Successfully!");
			} else {
				echo "<br>Running Query:<br>";
				echo ($sql.' - '.mysql_error($this->connectionID));
				util::logProblem('SQL Error - '.mysql_error($this->connectionID));
				util::alert("There was an error inserting your information into the database. Please try again or contact the administrator for assistance." . util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			}
		}
		$this->closeConn();
	}
		
	//this method assumes that there is an db connection that will be opened and closed by additional code so as to reduce the number of connections made
	//to the database when there will be many queries made at once
	public function runBatchMode($sql)
	{		
		if(substr($sql, 0, 6) == "SELECT")
		{
			$result = mysql_query($sql) or die(util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			return($result);
		} else {
			if(!mysql_query($sql)){
				//util::error("There was an error inserting your information into the database. Please try again or contact the administrator for assistance." . util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			}
		}
	}
	
	public function exists($table, $col, $ID)
	{
		$this->openConn();
		$sql = "SELECT COUNT(*) FROM $table where $col = '$ID' LIMIT 1";
		$result = mysql_query($sql) or die(util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
		$row = mysql_fetch_array($result);
		if ($row['COUNT(*)'] != '0')
		{
			return true;
		} else {
			return false;
		}
		$this->closeConn();
	}
	
	//use this function when you perform an insert on a table that uses autoIncrement 
	//and you want to capture and return the ID of the row that was just created
	public function insertAndCapture($sql)
	{
		$this->openConn();
		
		//run sql
		if(!mysql_query($sql)){
				//util::alert($sql);
				//util::logProblem('SQL Error - '.mysql_error($this->connectionID));
				//util::error("There was an error inserting your information into the database. Please try again or contact the administrator for assistance." . util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
				$insertID = false;
		}else{		
			//capture ID of insert
			$sql = "SELECT LAST_INSERT_ID() AS LastID";		
			$result = mysql_query($sql); // or die(util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
			$row = mysql_fetch_array($result);
			$insertID = $row['LastID'];			
		}
		$this->closeConn();
		return $insertID;
	}
	
	public function insertAndCaptureDebug($sql)
	{
		$this->openConn();
		
		//run sql
		if(!mysql_query($sql)){
				echo("<p>Running Query:</p>");
				echo($sql.' - '.mysql_error($this->connectionID)."<p>");
				util::alert("There was an error inserting your information into the database. Please try again or contact the administrator for assistance." . util::logProblem('SQL Error - '.mysql_error($this->connectionID)));
				$insertID = false;
		}else{		
			echo("<p>Running Query:</p>");
			echo($sql.' - '.mysql_error($this->connectionID)."<p>");
			util::alert("Query ran successfully!");
			//capture ID of insert
			$sql = "SELECT LAST_INSERT_ID() AS LastID";		
			$result = mysql_query($sql) or die(util::logProblem('SQL Error - '.mysql_error($this->connectionID))); 
			$row = mysql_fetch_array($result);
			$insertID = $row['LastID'];		
			echo("Last ID Inserted: ".$insertID."<p>");	
		}
		$this->closeConn();
		return $insertID;
	}
		
}
?>