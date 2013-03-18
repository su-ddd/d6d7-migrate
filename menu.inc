<?php

/**
 * Common mappings for the Drupal 6 user migrations.
 */
class d6d7MenuMigration extends DrupalMenu6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

  }

  // modify the source query
  protected function query() {
    //$query = parent::query();
	$query = Database::getConnection('default', 'legacy')
	  ->select('menu_links', 'm');
    $query->addField('m', 'menu_name', 'menu_name');
    $query->addField('m', 'link_title', 'title');
    $query->addField('m', 'link_title', 'description');
	$query->condition('m.module', 'book', '=');
	$query->condition('m.depth', 1, '=');
	$query->condition('link_title', '%RETIRED%', 'NOT LIKE');
    return $query;
  }

  public function prepareRow($row) {
    parent::prepareRow($row);
  }
}
