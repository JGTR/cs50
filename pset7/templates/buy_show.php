<div class="col-md-6 col-md-offset-3">
	<h1>Congrats on buying <?= $buy["symbol"] ?> </h1>
	<p>Price per share: <?= "$". money_format('%i', $buy["price"]) ?> </p>
	<p>Number of shares: <?= $buy["number_of_shares"] ?> </p>
	<p>You spent: <?= "$". money_format('%i', $buy["price"] * $buy["number_of_shares"]) ?> </p>
</div>
