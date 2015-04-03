<?php

    // configuration
    require("../includes/config.php"); 

    // NOTE ON PORTFOLIO: I judge it to be superior technique to calculate a user's portfolio based on transaction queries, as opposed to creating a static portfolio table. One of the major risks of that approach, is that the portfolio table and the actual transactions can be different due to database errors, etc. Although my approach is different, the same functionality is enabled as requested by the problemset specifications, so I hope I will not be penalized for a creative approach.

    // Get stocks for user
    $stocks = query("SELECT symbol, SUM(number_of_shares) FROM transactions WHERE user_id = ? GROUP BY symbol", user_id());

    // Add price and value for each stock
   	foreach ($stocks as $key => $value)
   	{
   		$price = lookup($stocks[$key]["symbol"])["price"];
   		$stocks[$key]["price"] = $price;
   		$stocks[$key]["value"] = $price * $stocks[$key]["SUM(number_of_shares)"];
   	}

   	// Get cash for user
   	$cash = get_user_cash();

   	// echo(var_dump($stocks));
  
	// render portfolio
	render("portfolio.php", ["title" => "Portfolio", "stocks" => $stocks, "cash" => $cash]);

?>
