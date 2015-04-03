<div class="col-md-10 col-md-offset-1">
	<h1> Your awesome portfolio!</h1>
	<div class="panel panel-default">
	  <div class="panel-heading">Available cash: <?= "$" . money_format("%i", $cash) ?> </div>


	  <table id="portfolio" class="table">
	  	<thead>
	  		<tr>
		  		<th>Symbol</th>
		  		<th>Number of Shares</th>
		  		<th>Price</th>
		  		<th>Current Value</th>
		  	</tr>
	  	</thead>
	  	<tbody>
		  	<?php foreach($stocks as $stock) : ?>
		  		<tr>
		  			<th> <?= $stock["symbol"] ?> </th>
		  			<td> <?= $stock["SUM(number_of_shares)"] ?> </td>
		  			<td> <?= "$". money_format("%i", $stock["price"]) ?> </td>
		  			<td> <?= "$". money_format("%i", $stock["value"]) ?> </td>
		  		</tr>
		  	<?php endforeach ?>
	  	</tbody>
	  </table>
	</div>

	<div class="logout">
	    <a href="logout.php">Log Out</a>
	</div>
</div>