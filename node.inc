<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class d6d7NodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * Catalog Entry mappings and handling
 */
class d6d7CatalogEntryMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // map the service catalog content to the body
    $this->addFieldMapping('body', 'field_service_catalog');

    // map the path (e.g. services/afs) to the url field
	// other options with field_links are field_links:title, etc.
    $this->addFieldMapping('field_links', 'path');

    // setting the format of the body to full_html
	// had to change the content type to accept user-provided formats
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    // don't import the path, we want the new IDs since the paths
	// point to the service pages
    $this->removeFieldMapping('path');

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid')->callbacks(array($this, 'calcID'));
    $this->addFieldMapping('is_new')->defaultValue('TRUE');
  }

  // This function adds 10000 to the node ID to avoid conflicts since this
  // is a new content type (for other nodes, we'll likely keep the same ID
  protected function calcID($value) {
    $value = $value + 10000;
    drupal_set_message($value);
    return $value;
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
	// TODO: add a condition to only import nodes published in the catalog
    $query->condition('status', '1', '=');
    return $query;
  }
}
  /**
   * Implementation of Migration::prepareRow().
   *
   * Here we pull in additional data from a non-core, non-CCK table.
   *
   * @param $row
   */
/*
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $image_row = Database::getConnection('default', $this->sourceConnection)
                 ->select('custom_image_table', 'i')
                 ->fields('i', array('copyright', 'filename'))
                 ->condition('vid', $row->vid)
                 ->execute()
                 ->fetchObject();
    if ($image_row) {
      $row->copyright = $image_row->copyright;
      $row->filename = $image_row->filename;
    }
    else {
      $this->saveMessage(t('No custom_image_table data for image node with vid !vid',
                         array('!vid' => $row->vid)));
    }
  }
}

class ExampleArticleMigration extends ExampleNodeMigration {
  public function __construct(array $arguments) {
    // Add any other data we're pulling into the source row, before the parent
    // constructor.
    $this->sourceFields['lead_graphic'] = 'Lead graphic string from D6';
    $this->sourceFields['summary'] = 'Summary string from D6';

    parent::__construct($arguments);

    $this->addFieldMapping('field_image', 'field_lead_graphic')
         ->sourceMigration('Image');
    // Note that we map migrated terms by the vocabulary ID.
    $this->addFieldMapping('field_countries', '1')
         ->sourceMigration('Countries')
         ->arguments(array('source_type' => 'tid'));
    $this->addFieldMapping('field_topics', '2')
         ->sourceMigration('Topics')
         ->arguments(array('source_type' => 'tid'));
  }
}
*/
