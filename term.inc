<?php

/**
 * Common mappings for the Drupal 6 term migrations.
 */

abstract class d6d7TermMigration extends DrupalTerm6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    //$this->addFieldMapping('field_legacy_nid', 'nid')
     //    ->description('We have a common field to save the D6 nid');
  }
}

/**
 * Catalog Categories specific mappings and handling.
 */
class d6d7CatalogCategoriesMigration extends d6d7TermMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->systemOfRecord = Migration::DESTINATION;
    $this->addFieldMapping('tid', 'tid');
  }

 public function preImport() {
    parent::preImport();

    $vocabs = taxonomy_vocabulary_get_names();

    $vid = $vocabs[$this->destination->getBundle()]->vid;
    //$query = $this->query;
    $query = Database::getConnection('default', 'legacy')
         ->select('term_data', 't')
         ->fields('t', array('tid'))
         ->condition('t.vid', 1, '=');
    if ($this->getItemLimit()>0) {
      $query->range(0, $this->getItemLimit());
    }
    $results = $query->execute()->fetchAllAssoc('tid');
    foreach ($results as $tid=>$result) {
      if (!taxonomy_term_load($tid)) {
        $term = new StdClass();
        $term->tid = $tid;
        $term->name = 'Stub term: ' . $tid;
        $term->description = '';
        $term->vid = $vid;
        $status = drupal_write_record('taxonomy_term_data', $term);

        db_merge('taxonomy_term_hierarchy')
          ->key(array('tid' => $term->tid))
          ->fields(array('tid' => $term->tid))
          ->execute();
      }
    }
  }
}

/**
 * Service Provider Categories
 */

class d6d7ServiceProvidersMigration extends d6d7TermMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->systemOfRecord = Migration::DESTINATION;
    $this->addFieldMapping('tid', 'tid');
  }

 public function preImport() {
    parent::preImport();

    $vocabs = taxonomy_vocabulary_get_names();

    $vid = $vocabs[$this->destination->getBundle()]->vid;
    //$query = $this->query;

	// 3 is the vocabulary ID for the original service providers vocabulary
    $query = Database::getConnection('default', 'legacy')
         ->select('term_data', 't')
         ->fields('t', array('tid'))
         ->condition('t.vid', 3, '=');

    if ($this->getItemLimit()>0) {
      $query->range(0, $this->getItemLimit());
    }

    $results = $query->execute()->fetchAllAssoc('tid');
    foreach ($results as $tid=>$result) {
      if (!taxonomy_term_load($tid)) {
        $term = new StdClass();
        $term->tid = $tid;
        $term->name = 'Stub term: ' . $tid;
        $term->description = '';
        $term->vid = $vid;
        $status = drupal_write_record('taxonomy_term_data', $term);

        db_merge('taxonomy_term_hierarchy')
          ->key(array('tid' => $term->tid))
          ->fields(array('tid' => $term->tid))
          ->execute();
      }
    }
  }
}
