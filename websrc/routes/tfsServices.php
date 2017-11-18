<?php
/**
 * Created by PhpStorm.
 * User: Abomy
 * Date: 10/05/2017
 * Time: 6:02 PM
 */

use \Psr\Http\Message\ServerRequestInterface as Request;
use \Psr\Http\Message\ResponseInterface as Response;


// Save new checkin
$app->post('/api/newCheckin', function(Request $request, Response $response){

    $json = json_decode($request->getBody(), true);

    print_r($json);
    error_log("===================== NEW SHIT ==========");


    $commit_id = $json['resource']['changesetId'];
    $comment = $json['message']['text'];
    $author = $json['resource']['checkedInBy']['displayName'];

    error_log($commit_id." | ".$comment." | ".$author);

    if ($commit_id) {

        $sql = "INSERT INTO `checkins` (`commit_id`,`comment`,`author`) VALUES (:commit_id,:comment,:author)";

        try{

            $stmt = db::insert($sql);
            $stmt->bindParam(':commit_id', $commit_id);
            $stmt->bindParam(':comment',  $comment);
            $stmt->bindParam(':author',   $author);

            $stmt->execute();


            echo '{"notice": {"text": "Commit added"}';
        } catch(PDOException $e){
            echo '{"error": {"text": '.$e->getMessage().'}}';
            error_log($e->getMessage());
        }
    } else {
        echo '{"error": {"text": "Error"}}';
    }
});