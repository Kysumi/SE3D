<?php
    use \Psr\Http\Message\ServerRequestInterface as Request;
    use \Psr\Http\Message\ResponseInterface as Response;


    require '../vendor/autoload.php';
    require '../config/db.php';
    require '../modules/ApiKey.php';


$config = [
    'settings' => [
        'displayErrorDetails' => true

    ],
];


$app = new \Slim\App($config);

$app->options('/{routes:.+}', function ($request, $response, $args) {
    return $response;
});

$dbhandler = new db();

$app->add(function ($req, $res, $next) {
    $response = $next($req, $res);
    return $response
        ->withHeader('Access-Control-Allow-Origin', '*')
        ->withHeader('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, Accept, Origin, Authorization')
        ->withHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
});


    $app->get('/hello/{name}', function (Request $request, Response $response) {
        $name = $request->getAttribute('name');
        $response->getBody()->write("Hello, $name");

        return $response;
    });

require '../routes/highscores.php';
require '../routes/tfsServices.php';

    $c = $app->getContainer();
    $c['errorHandler'] = function ($c) {
        return function ($request, $response, $exception) use ($c) {
            return $c['response']->withStatus(500)
                ->withHeader('Content-Type', 'text/html')
                ->write(file_get_contents("./404/index.html"));
        };
    };

    $c['notAllowedHandler'] = function ($c) {
        return function ($request, $response, $exception) use ($c) {
            return $c['response']->withStatus(404)
                ->withHeader('Content-Type', 'text/html')
                ->write(file_get_contents("./404/index.html"));
        };
    };
    $c['notFoundHandler'] = function ($c) {
        return function ($request, $response) use ($c) {
            return $c['response']
                ->withStatus(404)
                ->withHeader('Content-Type', 'text/html')
                ->write(file_get_contents("./404/index.html"));
        };
    };
    $app->run();