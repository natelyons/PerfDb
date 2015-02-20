<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of test_run_environment
 *
 * @author nlyons
 */
require_once('db.inc');

class test_run_environment {
    
    //declare attributes
    private $id;
    private $environment_property;
    private $property_value;
    private $test_run_id;

    //Set methods 
    public function setId($p) { $this->id = $p; } 
    public function setEnvironment_property($p) { $this->environment_property = $p; } 
    public function setProperty_value($p) { $this->property_value = $p; } 
    public function setTest_run_id($p) { $this->test_run_id = $p; } 


    //Get methods 
    public function getId() { return $this->id; }
    public function getEnvironment_property_id() { return $this->environment_property; }
    public function getProperty_value() { return $this->property_value; } 
    public function getTest_run_id() { return $this->test_run_id; }
    
    
    public function createObject(){
    //this function takes in an environment property value pair and does an insert into test_run_environment for a given test run.
        $db = new db();
           $sql = "INSERT INTO test_run_environment (environment_property, property_value, test_run_id) VALUES('" . $this->environment_property . "', '" . $this->property_value . "', " . $this->test_run_id . ")";
           //echo($sql);
           $db->run($sql);
    }
    
    
    //this function returns an array of distinct environment strings, along with the id of a test run that uses that environment
        public function getAllEnvironments($testFamId){
            //$arrEnv = array();
            $sql = "SELECT environment_property, property_value, count(test_run_id) as test_run_count
                    from test_run_environment
                    where test_run_id in (select id from test_run where test_fam_id = $testFamId)
                    group by environment_property, property_value
                    order by environment_property, count(test_run_id) desc";            
            $db = new db();
            $result = $db->run($sql);
            $i = 0;
            while ($row = mysql_fetch_array($result)){
                $arrEnv[$i] = array(env_prop => $row['environment_property'], prop_val => $row['property_value'], run_count => $row['test_run_count']) ;
                $i++;
            }
            //print_r($arrEnv);
            return $arrEnv;
        }
    
}
