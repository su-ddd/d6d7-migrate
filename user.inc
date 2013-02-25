<?php

/**
 * Common mappings for the Drupal 6 user migrations.
 */
abstract class d6d7UserMigration extends DrupalUser6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Keep the same UID's
    $this->addFieldMapping('is_new')->defaultValue('TRUE');
	$this->addFieldMapping('uid', 'uid');
  }

  // modify the source query
  protected function query() {
    $query = parent::query();
    
	$query->distinct();
    return $query;
  }
}

/**
 * Business Owners
 */
class d6d7BusinessOwnerMigration extends d6d7UserMigration {
  // modify the source query
  protected function query() {
    $query = parent::query();
    
	$query->join('content_type_service', 'cts', 'cts.field_service_business_owner_uid = u.uid');
    return $query;
  }
}

/**
 * Technical Owners
 */
class d6d7TechnicalOwnerMigration extends d6d7UserMigration {
  // modify the source query
  protected function query() {
    $query = parent::query();

    $query->join('content_type_service', 'cts', 'cts.field_service_technical_owner_uid = u.uid');
    return $query;
  }
}

/**
 * Service Manager
 */
class d6d7ServiceManagerMigration extends d6d7UserMigration {
  // modify the source query
  protected function query() {
    $query = parent::query();

    $query->join('content_type_service', 'cts', 'cts.field_service_manager_uid = u.uid');
    return $query;
  }
}

/**
 * Operations Owners
 */
class d6d7OperationsOwnerMigration extends d6d7UserMigration {
  // modify the source query
  protected function query() {
    $query = parent::query();

    $query->join('content_type_service', 'cts', 'cts.field_service_operations_owner_uid = u.uid');
    return $query;
  }
}

