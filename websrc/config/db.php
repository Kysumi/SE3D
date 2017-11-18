<?php

/**
 * Created by PhpStorm.
 * User: Abomy
 * Date: 7/05/2017
 * Time: 3:41 PM
 */
class db
{
        private $host = 'localhost';
        private $user = 'root';
        private $pass = '$Love4meplx';
        private $table = 'SE3D';

         // Connect
        public function connect(){
        $mysql_connect_str = "mysql:host=$this->host;dbname=$this->table";
        $dbConnection = new PDO($mysql_connect_str, $this->user, $this->pass);
        $dbConnection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        return $dbConnection;
    }

}