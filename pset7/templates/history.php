<div class="col-md-10 col-md-offset-1">
	<div class="panel panel-default">
	  <div class="panel-heading">Your awesome history!</div>


	  <table id="history" class="table">
	  	<thead>
	  		<tr>
		  		<th>Symbol</th>
		  		<th>Type</th>
		  		<th>Number of Shares</th>
		  		<th>Price</th>
		  		<th>Amount</th>
		  		<th>Time</th>
		  	</tr>
	  	</thead>
	  	<tbody>
		  	<?php foreach($transactions as $transaction) : ?>
		  		<tr>
		  			<th> <?= $transaction["symbol"] ?> </th>
		  			<td> <?= $transaction["type"] ?> </th>
		  			<td> <?= $transaction["number_of_shares"] ?> </td>
		  			<td> <?= "$". money_format("%i", $transaction["price"]) ?> </td>
		  			<td> <?= "$". money_format("%i", $transaction["amount"]) ?> </td>
		  			<td> <?= $transaction["created_at"] ?> </td>
		  		</tr>
		  	<?php endforeach ?>
	  	</tbody>
	  </table>
	</div>

	<div class="logout">
	    <a href="logout.php">Log Out</a>
	</div>
</div>