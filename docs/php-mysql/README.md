# Dynamische sensorlijst met PHP en MySQL

## Database met MySQL

### PHPmyAdmin

```sql
CREATE TABLE `sensors` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `unit` varchar(255)  NOT NULL,
  `topic` varchar(255) NOT NULL,
  `value` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE utf8_bin;
```

## PHP

```php
<?php

$host = '127.0.0.1';
$db   = 'workshop';
$user = 'root';
$pass = '';

$dsn = "mysql:host=$host;dbname=$db;charset=utf8mb4";

try {
     $pdo = new PDO($dsn, $user, $pass);
     $stmt = $pdo->query('SELECT * FROM sensors');
     $data = $stmt->fetchAll(PDO::FETCH_ASSOC);
     header('Content-Type: application/json');
     echo json_encode($data);
} catch (PDOException $e) {
     throw new PDOException($e->getMessage(), (int)$e->getCode());
}
```

## Aanpassen JavaScript


Verwijderen van: 

```js
const sensorList = [
        {
          name: "hello",
          value: "-",
          unit: '°C',
          topic: 'workshop/temperature'
        },
      ...
      ] 
```


Vervangen door

```js
const api_url = "sensors.php";

axios.get(api_url)
  .then((response) => {
    app.$data.sensors = response.data;
  }) 
```

Data van de Vue app herinstellen


```js{2}
    data: {             
      sensors: sensorList 
    },
```

```js{2}
    data: {             
      sensors: [] 
    },
```