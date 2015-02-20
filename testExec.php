<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//error_reporting(E_ALL);
//ini_set("display_errors", 1);

require_once './includes/db.inc';
require_once './includes/testrun.inc';
require_once './includes/test_execution_metric.inc';
require_once './includes/test_execution.inc';
date_default_timezone_set("America/Denver"); 

$strInput = file_get_contents('php://input');
$arrInput = json_decode($strInput, true);
//print_r ($objInput);
$jsonOutput = '';

//*******************************************************
//Create a new test execution record
//*******************************************************
if ($arrInput['method'] == "startTest"){
    
    //sample json to post to http://moab-walldisplay.ac/perfdb/testExec.php
    /*
     {
        "method": "startTest",
        "version":"0",
        "test_run_id":"7",
        "description": "a test is being executed",
        "external_id": "testid_xvii"
     }
     */
    
    //create a new test run record in the database
    $objTestExec = new test_execution();
    $objTestExec->setTest_run_id(mysql_real_escape_string($arrInput['test_run_id']));
    $objTestExec->setVersion(mysql_real_escape_string($arrInput['version']));
    $objTestExec->setDescription(mysql_real_escape_string($arrInput['description']));
    $objTestExec->setDuration(-1); //duration gets set to -1 on create.  It will be calculated on test run completion
    //$objTestRun->setEnd_date('');
    $objTestExec->setExternal_id(mysql_real_escape_string($arrInput['external_id']));
    $objTestExec->setStart_date(date("Y-m-d H:i:s"));
    
    $intTestExecId = $objTestExec->createObject();
    //echo('timestamp = ' . $objTestExec->getStart_date() . '<br>')
    
    //Return json status of operation
    $jsonOutput = array("status" => 1, "msg" => "attempted to create a new test execution record", "test_exec_id" => $intTestExecId); //if the test_run_id is null, that means the record could not be created.
   
    
    
    
//*********************************************************
//Add Metrics to a test execution
//*********************************************************    
}elseif ($arrInput['method'] == "addMetrics"){ 
 //sample json to post
   /*
    {  
        "method": "addMetrics",
        "test_exec_id":"3",
        "property_values":
        {  
           "0":{  
              "metric_id":"3",
              "metric_value":"15.3"
           },
           "1":{  
              "metric_id":"4",
              "metric_value":".54"
           }
        }
    }
    */
    $i = 0;
    $objTEM = new test_execution_metric();
    $objTEM->setTest_execution_id($arrInput['test_exec_id']);
    foreach ($arrInput['property_values'] as $pv){
        $objTEM->setMetric_id($pv['metric_id']);
        $objTEM->setMetric_value($pv['metric_value']);
        $objTEM->createObject();
        $i++;
    }
    
    
    $jsonOutput = array("test_exec_id" => $arrInput['test_exec_id'], "te_metric_records_created" => $i);



//*********************************************************
//End an existing test execution
//*********************************************************    
}elseif ($arrInput['method'] == "endExec"){
    //*****TO DO - copied from testRun... needs updates   
    
    //sample json to post to http://moab-walldisplay.ac/perfdb/testRun.php
    /*
     {
        "method": "endExec",
        "te_id": "3",
        "result":"1"
     }
     */
    
    //update an existing test_run record with and end_datetime and duration.
    $objTestExec = new test_execution();
    $objTestExec->getObject(mysql_real_escape_string($arrInput['te_id']));
    $objTestExec->setResult(mysql_real_escape_string($arrInput['result']));
    $objTestExec->setEnd_date(date("Y-m-d H:i:s"));
    
    $objTestExec->endExec();
    //echo('timestamp = ' . $objTestRun->getStart_date() . '<br>')
    
    //Return json status of operation
    $jsonOutput = array("status" => 1, "msg" => "attempted to end test execution", "test_exec_id" => $objTestExec->getId(), "duration" => $objTestExec->getDuration()); 
    
    
}else{
    $jsonOutput = array("status" => 0 , "msg" => "Request method not accepted", "method_called" => $objInput->{'method'});
}




header('Content-type: application/json');
echo json_encode($jsonOutput);

?>