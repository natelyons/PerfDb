<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of testrun
 *
 * @author nlyons
 */

require_once('db.inc');

class test_run {
//declare attributes
		
	private $id;
        private $version;
        private $description;
        private $duration;
        private $end_date;
        private $external_id;
        private $is_manual;
        private $run_by;
        private $start_date;
        private $clean_end;
        private $test_fam_id;
	
	
	//Set methods 
	public function setId($p) { $this->id = $p; } 
        public function setVersion($p) { $this->version = $p; } 
        public function setDescription($p) { $this->description = $p; } 
        public function setDuration($p) { $this->duration = $p; } 
        public function setEnd_date($p) { $this->end_date = $p; } 
        public function setExternal_id($p) { $this->external_id = $p; } 
        public function setIs_manual($p) { $this->is_manual = $p; } 
        public function setRun_by($p) { $this->run_by = $p; } 
        public function setStart_date($p) { $this->start_date = $p; } 
	public function setClean_end($p) { $this->clean_end = $p; } 
        public function setTest_fam_id($p) { $this->test_fam_id = $p; }
	
	//Get methods 
	public function getId() { return $this->id; } 
        public function getVersion() { return $this->version; } 
        public function getDescription() { return $this->description; } 
        public function getDuration() { return $this->duration; } 
        public function getEnd_date() { return $this->end_date; } 
        public function getExternal_id() { return $this->external_id; } 
        public function getIs_manual() { return $this->is_manual; } 
        public function getRun_by() { return $this->run_by; } 
        public function getStart_date() { return $this->start_date; } 
        public function getClean_end() { return $this->clean_end; }
        public function getTest_fam_id() { return $this->test_fam_id; } 
        
        
        //Method to check the validity of the object
	private function isValid()
	{
            $blnIsValid = true;
            return $blnIsValid;
            
        }
        
        public function getObject($tr_id){
            $sql = "SELECT * FROM test_run WHERE id = " . $tr_id . " LIMIT 1";
            $db = new db();
            $result = $db->run($sql);
            while ($row = mysql_fetch_array($result)){
                $this->id = $row['id'];
                $this->version = $row['version'];
                $this->description = $row['description'];
                $this->duration = $row['duration'];
                $this->end_date = $row['end_date'];
                $this->external_id = $row['external_id'];
                $this->is_manual = $row['is_manual'];
                $this->run_by = $row['run_by'];
                $this->start_date = $row['start_date'];
                $this->clean_end = $row['clean_end'];
                $this->test_fam_id = $row['test_fam_id'];
                
            }
        }
        
        public function createObject(){
            $sql = "INSERT INTO test_run (version, description, duration, end_date, external_id, is_manual, run_by, start_date, test_fam_id) "
                    . "VALUES ($this->version, '$this->description', '$this->duration', '$this->end_date', '$this->external_id', $this->is_manual, '$this->run_by', '$this->start_date', $this->test_fam_id)";
            $newId = 0;
            if($this->isValid() == true){
                $db = new db();
                $newId = $db->insertAndCapture($sql);
            }else{
                    echo("Error attempting to create object: object is invalid");
            }
            return $newId;
        }
        
        public function endRun(){
            //assumes that you are starting from a fully populated, previously persisted object (use test_run->getObject() first)
            
            //calculate duration
            $objStartDate = new DateTime($this->start_date);
            $objEndDate = new DateTime($this->end_date);
            $dateDiff = $objEndDate->diff($objStartDate);
            $strDiff = $dateDiff->format('%D:%H:%I:%S'); //number of days:hours:minutes:seconds between the start and end dates  ***Note, this currently does not handle tests that run longer than 1 month.  The month gets dropped
            $this->duration = $strDiff;
            
            //update test_run record
            $sql = "UPDATE test_run SET " .
                    "end_date = '" . $this->end_date . "', " .
                    "duration = '" . $this->duration . "', " .
                    "clean_end = " . $this->clean_end . " " .
                    "WHERE id = " . $this->id;
            $db = new db();
            $db->run($sql);
        }
        
        public function getTestRunsByEnvironment($arrEnv){
            //the array that this function expects as an input is environment properties and values seperated by a "|" for each element of the array.
            //example: Array ( [0] => insight_server_memory|16 [1] => insight_server_name|qt23.ac [2] => moab_server_cores|16 [3] => moab_server_memory|32 )
            $sql = "SELECT * FROM v_tr_env_flat WHERE 1 = 1 ";
            //build where clause
            $strWhere = '';
            foreach ($arrEnv as $strEnv){
                $strWhere .= ' and prop_vals like "%' . $strEnv . '%"';
            }
            $sql .= $strWhere;          
            
            $arrTR = array();           
            $db = new db();
            $result = $db->run($sql);
            $i = 0;
            while ($row = mysql_fetch_array($result)){
                $arrTR[$i] = $row['test_run_id'];
                $i++;
            }
            
            //returns an array of all test_run_ids that match all environment criteria
            return $arrTR;
        }
        
}    
?>        
