<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Name of testrun
 *
 * @author nlyons
 */

require_once('db.inc');

class test_family {
//declare attributes
		
	private $id;
        private $name;
        private $description;
        private $info_link;

	
	
	//Set methods 
	public function setId($p) { $this->id = $p; }          
        public function setName($p) { $this->name = $p; } 
        public function setDescription($p) { $this->description = $p; } 
        public function setInfo_link($p) { $this->info_link = $p; } 
        
	
	//Get methods 
	public function getId() { return $this->id; }          
        public function getName() { return $this->name; } 
        public function getDescription() { return $this->description; } 
        public function getInfo_link() { return $this->info_link; } 
        
        
        
        //Method to check the validity of the object
	private function isValid()
	{
            $blnIsValid = true;
            return $blnIsValid;
            
        }
        
        public function getObject($tf_id){
            $sql = "SELECT * FROM test_family WHERE id = " . $tf_id . " LIMIT 1";
            $db = new db();
            $result = $db->run($sql);
            while ($row = mysql_fetch_array($result)){
                $this->id = $row['id'];                
                $this->name = $row['name'];
                $this->description = $row['description'];
                $this->info_link = $row['info_link'];
                
            }
        }
        
        //this function returns an array of testfamily objects
        public function getAll(){
            $arrTF = array();
            $sql = "SELECT * FROM test_family ORDER BY name";            
            $db = new db();
            $result = $db->run($sql);
            $i = 0;
            while ($row = mysql_fetch_array($result)){
                $arrTF[$i] = new test_family();
                $arrTF[$i]->id = $row['id'];
                $arrTF[$i]->name = stripslashes($row['name']);
                $arrTF[$i]->description = stripslashes($row['description']);
                $arrTF[$i]->info_link = $row['info_link'];
                $i++;
            }
            return $arrTF;
        }
        
        public function createObject(){
            $sql = "INSERT INTO test_family (name, description, info_link) "
                    . "VALUES ('$this->name', '$this->description', '$this->info_link')";
            $newId = 0;
            if($this->isValid() == true){
                $db = new db();
                $newId = $db->insertAndCapture($sql);
            }else{
                    echo("Error attempting to create object: object is invalid");
            }
            return $newId;
        }
        
        
        
        
}    
?>        
