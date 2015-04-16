<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
    $geo = $_GET["geo"];
    $geo = str_replace(",", " ", $geo);
    $geo = trim($geo);

    // Count how many words were entered into the search
    $geo = explode(" ", $geo);
    $count = count($geo);

    // Error out if the user did not provide input
    if ($count < 1)
    {
    	print("Please enter a query string.");
    }
    elseif ($count === 1)
    {
    	$geo = $geo[0];
    	// Check zipcode if the length of the string is 5 chars
    	if(strlen($geo) === 5)
    	{
    		$places = query("SELECT * FROM places WHERE postal_code = ?", $geo);	
    	}
    	elseif(strlen($geo) == 2)
    	{
    		// Check state abbreviation, called admin_code1
    		$places = query("SELECT * FROM places WHERE admin_code1 = ?", strtoupper($geo));
    	}
    	else
    	{
    		// Check city, called place_name in places table
    		$places = query("SELECT * FROM places WHERE place_name LIKE ?", $geo);
    	}
    	
    	if(empty($places))
    	{
    		// Check state, called admin_name1
    		$places = query("SELECT * FROM places WHERE admin_name1 LIKE ?", $geo);
    	}
    }
    elseif($count > 1)
    {
    	// Reassemble places into one long string
    	$geo = implode(" ", $geo);

    	// Search across multiple columns
    	$places = query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1, admin_code1) AGAINST (?)", $geo);
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
