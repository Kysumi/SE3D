<?php

//include '../config/db.php';

/**
 * Created by PhpStorm.
 * User: Abomy
 * Date: 7/05/2017
 * Time: 4:03 PM
 */
class ApiKey
{

    private $_valid = false;

    function __construct($key)
    {
        if($key == "gamerino")
            $this->_valid = true;
    }

    public function isValid()
    {
        return $this->_valid;
    }
}