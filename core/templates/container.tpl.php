<div class="region">
	<a href="<?=$this->titleurl?>" class="region-title"><?=$this->title?></a>
	<?=$this->prolog?>
	<?=implode("", $slots)?>
	<a href="<?=$this->readmoreurl?>"><?=$this->readmore?></a>
	<?=$this->epilog?>
</div>