<?php

ini_set("display_errors", 1);
error_reporting(E_ERROR);
date_default_timezone_set("America/Denver");
/*  
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

require_once './includes/testrun.inc';
require_once './includes/test_execution_metric.inc';
require_once './includes/test_execution.inc';
require_once './includes/test_family.inc';
require_once './includes/test_run_environment.inc';


$strSelectedTF = $_REQUEST['test_family'];
$arrSelectedEnv = $_REQUEST['env'];
$arrSelectedTE = $_REQUEST['test_exec'];
$strSelectedMetric = $_REQUEST['metric'];


$objTR = new test_run();
$arrSelectedTR = $objTR->getTestRunsByEnvironment($arrSelectedEnv);

print_r($arrSelectedTE);
//echo (implode("||", $arrSelectedEnv));

$arrActual_test = array(
                            '2014-06-01' => 122,
                            '2014-06-02' => 90,
                            //'2014-06-03' => 90,
                            //'2014-06-04' => 95,
                            '2014-06-05' => 100,
                            '2014-06-06' => 40,
                            '2014-06-07' => 20,
                            '2014-06-08' => 15
                        );
//echo array_values($arrActual_test)[0];


//create test family dropdown
function showTestFamilies($strSelectedTF){
    $html = '<select name="test_family">';
    $objTf = new test_family();
    $arrTf = $objTf->getAll();
    //print_r($arrTf);
    foreach ($arrTf as $tf){
        $selAtt = '';
        if($tf->getId() == $strSelectedTF){
            $selAtt = 'selected ';
        }
        $html = $html .
                '<option ' . $selAtt . 'value="' . $tf->getId() . '">' . $tf->getName() . '</option>';        
    }
    
    $html .= '</select>';
    return $html;
}

function showEnvironments($strSelectedTF, $strUseNames = false, $arrSelectedEnv){
    $html = '<select name="env[]" multiple="true" size="10">';
    $strSelectedEnv = implode("||", $arrSelectedEnv);
    //echo($strSelectedEnv);
    if ($strSelectedTF == ""){
        $html .= '<option value="">-----please select a test family-----</option>';
    }else{        
        $objEnv = new test_run_environment();
        $arrEnv = $objEnv->getAllEnvironments($strSelectedTF);
        foreach ($arrEnv as $env){
            $selAtt = '';
            $strValue = $env["env_prop"] . "|" . $env["prop_val"];
            $strDisplay = $env["env_prop"] . " = " . $env["prop_val"] . " (" . $env["run_count"] . " runs)";            
            if(substr_count($strSelectedEnv, $strValue) > 0){                
                $selAtt = 'selected ';
            }
            $html = $html .
                    '<option ' . $selAtt . 'value="' . $strValue . '">' . $strDisplay . '</option>';     
            
        }

        $html .= '</select>';
    }
    return $html;
}

function showTestRuns($arrSelectedTR){
    $html = '';
    $html .= '<b>' . count($arrSelectedTR) . '</b> runs match all selected criteria';
    $html .= '<input type="hidden" name="test_run[]" value="' . $arrSelectedTR . '">';
    return $html;
}


function showTestExecs($arrSelectedTR, $arrSelectedTE){
    $html = '<br><select name="test_exec[]" size="15">';
    if(count($arrSelectedTR) == 0){
        $html .= '<option value="">-----please select a valid set of enviroment properties-----</option>';
    }else{
        $objTEM = new test_execution_metric();
        $arrTE = $objTEM->getAllByTestRuns($arrSelectedTR);
        $strSelTes = implode("|", $arrSelectedTE);
        foreach($arrTE as $te){
            $selAtt = '';
            $strValue = $te['test_execution_id'] . '_' . $te['metric_id'];
            $strDisplay = $te['test_exec_desc'] . ' - ' . $te['metric_name'] . ' (' . $te['result_count'] . ' values)';
            if(substr_count($strSelTes, $strValue) > 0){                
                $selAtt = 'selected ';
            }
            $html .= '<option ' . $selAtt . ' value="' . $strValue . '">' . $strDisplay . '</option>';
        }
    }
    
    $html .= "</select>";
    return $html;
}

function showMetrics(){
    
}

function displayChart(){
    
}

function formatBurnDownData($startDate, $endDate, $arrActual, $intPrecision = 5)
{
    /* takes an array of dates and actual values (with dates as the array key) such as;
     * array(
                '2014-06-01' => 122,
                '2014-06-02' => 56,
                '2014-06-03' => 13
            );
     * uses the start and end dates passed into the function to create an ideal burndown line for the dataset
     *  and formats as shown below, so it can be easily passed to google chart for display
     * ['Date', 'Ideal', 'Actual'],
     * ['6/1',  122,      122],
     * ['6/2',  61,      56],
     * ['6/3',  0,      13],
     * Currently only handles daily burn downs, but could be altered to do weekly/monthly
     */
    
    $arrDataPoints = array();
    //figure out how many days are in the range
    $objStartDate = new DateTime($startDate);
    $objEndDate = new DateTime($endDate);
    $dateDiff = $objEndDate->diff($objStartDate);
    $intNumDays = intval($dateDiff->format('%d')); //number of days in the date range
    //$numBurndownStartVal = array_values($arrActual)[0]; // get the first value and use it to start the burndown
    
    $i = 0;
    $numNextIdeal = $numBurndownStartVal;
    $numIdealStep = $numBurndownStartVal / ($intNumDays + 1);
    $numMostrecentActualVal = $numBurndownStartVal;
    while ($i <= $intNumDays){
        $objNextDate = clone($objStartDate);
        $objNextDate->add(new DateInterval('P' .$i. 'D'));  
        
        if(!array_key_exists($objNextDate->format('Y-m-d'), $arrActual)){
            $numNextActual = $numMostrecentActualVal; //there was no value for that date, so fall back to the most recently found actual
        }else{
            $numNextActual = $arrActual[$objNextDate->format('Y-m-d')]; //there was an actual value for that date, so use and update the most recently found actual
            $numMostrecentActualVal = $numNextActual;
        }
        
        $arrDataPoints[$i] = array(
            $objNextDate,
            $numNextIdeal,
            $numNextActual
        );
        $numNextIdeal = $numNextIdeal - $numIdealStep;
        $i++;
    }
    
    //explode array into a formatted string to pass to google charts.
    $strFormattedData = "['Date', 'Ideal', 'Actual']";
    foreach ($arrDataPoints as $arrRow){
       //Column/element 0 of each row contains a date object.  Column 1 contains an Ideal value. column 2 contains an actual value
        $strFormattedData = $strFormattedData . ",\n";
       $strFormattedData = $strFormattedData . "['" . date_format($arrRow[0], 'n/j') . "', " . $arrRow[1] . ", " . $arrRow[2] . "]" ;
    }
    
    return $strFormattedData;
}


?>

<html>
<header>
</header>
    <body> 
        <table>
            <tr>
                <!--table to divide the page into 2 columns.  left column for the form to select the metrics.  right column to display metrics -->
                <td>
                    <form name="frmMetrics" action="<?php echo($_SERVER['PHP_SELF']); ?>" method="POST">
                    <?php
                        echo(showTestFamilies($strSelectedTF));
                        echo('<br>');
                        echo(showEnvironments($strSelectedTF, false, $arrSelectedEnv));
                        echo('<br>');
                        echo(showTestRuns($arrSelectedTR));
                        echo('<br>');
                        echo(showTestExecs($arrSelectedTR,$arrSelectedTE));
                    ?>
                        <br><br><input type="submit" name="btnSubmit" value="submit">
                    </form>
                    &nbsp;
                </td>
                <td>
                    
                    &nbsp;
                </td>
            </tr>
        </table>
<div class="half">
    <div class="block">
	<script type="text/javascript" src="https://www.google.com/jsapi"></script>
        <script type="text/javascript">
          google.load("visualization", "1", {packages:["corechart"]});
          google.setOnLoadCallback(drawChart);
          function drawChart() {
            var data = google.visualization.arrayToDataTable([
              <?php 
                    //echo(formatBurndownData('2014-06-01', '2014-06-15', $arrActual_test));
                    //echo(formatBurndownData('2014-09-02', '2014-10-15', $arrActual_test)); 
              ?>
            ]);

            var options = {
              title: 'Test Burndown'
            };

            var chart = new google.visualization.LineChart(document.getElementById('chart_div2'));
            chart.draw(data, options);
          }
        </script>

  
    <div id="chart_div2" style="width: 100%; height: 500px;"></div>
	
    </div>
</div>
        
</body>
</html>