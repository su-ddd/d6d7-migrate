<?php

/**
 * Common mappings for the Drupal 6 user migrations.
 */
abstract class d6d7UserMigration extends DrupalUser6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * User mappings and handling
 */
class d6d7WebAuthUserMigration extends d6d7UserMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Keep the same UID's
    $this->addFieldMapping('is_new')->defaultValue('TRUE');
	$this->addFieldMapping('uid', 'uid');
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

//    $query->condition('status', '1', '=');
    return $query;
  }
}
