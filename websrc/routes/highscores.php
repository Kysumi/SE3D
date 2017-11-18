<?php
/**
 * Created by PhpStorm.
 * User: Abomy
 * Date: 8/05/2017
 * Time: 9:15 PM
 */

use \Psr\Http\Message\ServerRequestInterface as Request;
use \Psr\Http\Message\ResponseInterface as Response;

// Get All Highscores
$app->get('/api/{apiKey}/highscores', function (Request $request, Response $response) {
    $sql = "SELECT * FROM Highscores";
    $apiKey = new ApiKey($request->getAttribute('apiKey'));
    if ($apiKey->isValid()) {
        try {
            $highscores = db::fetchAll($sql);
            echo json_encode($highscores);


        } catch (PDOException $e) {
            echo '{"error": {"text": ' . $e->getMessage() . '}}';
        }
    } else {
        echo '{"error": {"text": "Invalid Api key"}}';
    }
});

// Get player Highscores
$app->get('/api/{apiKey}/highscores/{id}', function (Request $request, Response $response) {
    $id = $request->getAttribute('id');
    $sql = "SELECT * FROM Highscores WHERE player_id = $id";
    $apiKey = new ApiKey($request->getAttribute('apiKey'));
    if ($apiKey->isValid()) {
        try {
            $highscores = db::fetchAll($sql);
            echo json_encode($highscores);
        } catch (PDOException $e) {
            echo '{"error": {"text": ' . $e->getMessage() . '}';
        }
    } else {
        echo '{"error": {"text": "Invalid Api key"}}';
    }
});

$app->post('/api/{apiKey}/highscores/add', function(Request $request, Response $response){

    $player_id = $request->getParam('player_id');
    $map_seed = $request->getParam('map_seed');
    $time = $request->getParam('time');

    echo    $player_id;

    $sql = "INSERT INTO `Highscores` (`player_id`,`map_seed`,`time`) VALUES (:player_id,:map_seed,:time)";
    try{

        $stmt = db::insert($sql);
        $stmt->bindParam(':player_id', $player_id);
        $stmt->bindParam(':map_seed',  $map_seed);
        $stmt->bindParam(':time',      $time);
        $stmt->execute();


        echo '{"notice": {"text": "Highscore Added"}';
    } catch(PDOException $e){
        echo '{"error": {"text": '.$e->getMessage().'}}';
    }
});
