<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of test_execution_metric
 *
 * @author nlyons
 */
require_once('db.inc');


class test_execution_metric {
    
    //declare attributes
    private $id;
    private $metric_id;
    private $metric_value;
    private $test_execution_id;

    //Set methods 
    public function setId($p) { $this->id = $p; } 
    public function setMetric_id($p) { $this->metric_id = $p; } 
    public function setMetric_value($p) { $this->metric_value = $p; } 
    public function setTest_execution_id($p) { $this->test_execution_id = $p; } 


    //Get methods 
    public function getId() { return $this->id; }
    public function getMetric_id() { return $this->metric_id; }
    public function getMetric_value() { return $this->metric_value; } 
    public function getTest_execution_id() { return $this->test_execution_id; }
    
    
    public function createObject(){
    //this function takes in a metric and value pair, and inserts into test_execution_metric for a given test execution.
        $db = new db();
           $sql = "INSERT INTO test_execution_metric (metric_id, metric_value, test_execution_id) VALUES(" . $this->metric_id . ", '" . $this->metric_value . "', " . $this->test_execution_id . ")";
           //echo($sql);
           $db->run($sql);
    }
    
    
    public function getAllByTestRuns($arrTR_id){
        //flatten array into comma seperated list
        $strTRs = implode(",", $arrTR_id);
        //$arrTems = array();
        $db = new db();
        $sql = "SELECT tem.test_execution_id, te.description as test_exec_desc, tem.metric_id, m.metric_name, count(*) as result_count 
                FROM test_execution_metric tem
                JOIN test_execution te on tem.test_execution_id = te.id
                JOIN metric m on m.id = tem.metric_id
                WHERE test_execution_id IN (SELECT id FROM test_execution WHERE test_run_id in ($strTRs))
                GROUP BY  tem.test_execution_id, te.description, tem.metric_id, m.metric_name
                ORDER BY te.description, m.metric_name";
        $result = $db->run($sql);
        $i = 0;
        while($row = mysql_fetch_array($result)){
            $arrTems[$i] = array("test_execution_id" => $row['test_execution_id'], "test_exec_desc" => $row['test_exec_desc'], "metric_id" => $row['metric_id'], "metric_name" => $row['metric_name'], "result_count" => $row['result_count']);
            $i++;
        }
        return $arrTems;
    }
}
