<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of test_execution
 *
 * @author nlyons
 */
require_once('db.inc');

class test_execution {
    //declare attributes
		
	private $id;
        private $version;
        private $description;
        private $duration;
        private $end_date;
        private $external_id;
        private $result;
        private $start_date;
        private $test_run_id;
	
	
	//Set methods 
	public function setId($p) { $this->id = $p; } 
        public function setVersion($p) { $this->version = $p; } 
        public function setDescription($p) { $this->description = $p; } 
        public function setDuration($p) { $this->duration = $p; } 
        public function setEnd_date($p) { $this->end_date = $p; } 
        public function setExternal_id($p) { $this->external_id = $p; } 
        public function setResult($p) { $this->result = $p; } 
        public function setStart_date($p) { $this->start_date = $p; } 
	public function setTest_run_id($p) { $this->test_run_id = $p; } 
	
	//Get methods 
	public function getId() { return $this->id; } 
        public function getVersion() { return $this->version; } 
        public function getDescription() { return $this->description; } 
        public function getDuration() { return $this->duration; } 
        public function getEnd_date() { return $this->end_date; } 
        public function getExternal_id() { return $this->external_id; } 
        public function getResult() { return $this->result; } 
        public function getStart_date() { return $this->start_date; } 
        public function getTest_run_id() { return $this->test_run_id; }
        
        
        //Method to check the validity of the object
	private function isValid()
	{
            $blnIsValid = true;
            return $blnIsValid;
            
        }
        
        public function getObject($te_id){
            $sql = "SELECT * FROM test_execution WHERE id = " . $te_id . " LIMIT 1";
            $db = new db();
            $result = $db->run($sql);
            while ($row = mysql_fetch_array($result)){
                $this->id = $row['id'];
                $this->version = $row['version'];
                $this->description = $row['description'];
                $this->duration = $row['duration'];
                $this->end_date = $row['end_date'];
                $this->external_id = $row['external_id'];
                $this->result = $row['result'];
                $this->start_date = $row['start_date'];
                $this->test_run_id = $row['test_run_id'];
                
            }
        }
        
        public function createObject(){
            $sql = "INSERT INTO test_execution (version, description, duration, external_id, start_date, test_run_id) "
                    . "VALUES ($this->version, '$this->description', '$this->duration', '$this->external_id', '$this->start_date', $this->test_run_id)";
            //echo $sql;
            $newId = 0;
            if($this->isValid() == true){
                $db = new db();
                $newId = $db->insertAndCapture($sql);
            }else{
                    echo("Error attempting to create object: object is invalid");
            }
            return $newId;
        }
        
        public function endExec(){
            //assumes that you are starting from a fully populated, previously persisted object (use test_execution->getObject() first)
            
            //calculate duration
            $objStartDate = new DateTime($this->start_date);
            $objEndDate = new DateTime($this->end_date);
            $dateDiff = $objEndDate->diff($objStartDate);
            $strDiff = $dateDiff->format('%D:%H:%I:%S'); //number of days:hours:minutes:seconds between the start and end dates  ***Note, this currently does not handle tests that run longer than 1 month.  The month gets dropped
            $this->duration = $strDiff;
            
            //update test_execution record
            $sql = "UPDATE test_execution SET " .
                    "end_date = '" . $this->end_date . "', " .
                    "duration = '" . $this->duration . "', " .
                    "result = '" . $this->result . "' " .
                    "WHERE id = " . $this->id;
            $db = new db();
            $db->run($sql);
        }
        
     
}
