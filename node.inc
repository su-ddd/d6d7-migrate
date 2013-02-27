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
    $this->addFieldMapping('field_catalog_entry_link', 'path');

    // setting the format of the body to full_html
	// had to change the content type to accept user-provided formats
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    // don't import the path, we want the new IDs since the paths
	// point to the service pages
    $this->removeFieldMapping('path');

	// Map the catalog category to this field, and use the tid to make the match
	$this->addFieldMapping('field_catalog_entry_categories', 1);
    $this->addFieldMapping('field_catalog_entry_categories:source_type')->defaultValue('tid');

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid')->callbacks(array($this, 'calcID'));
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    // Destination fields ignored
   $this->addFieldMapping('field_catalog_entry_link:title', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
   $this->addFieldMapping('field_catalog_entry_link:attributes', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
   $this->addFieldMapping('field_catalog_entry_link:language', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
  }

  // This function adds 10000 to the node ID to avoid conflicts since this
  // is a new content type (for other nodes, we'll likely keep the same ID
  protected function calcID($value) {
    $value = $value + 10000;
    return $value;
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes and those that are marked with the "Service Catalog" term
    $query->join('term_node', 'td', 'n.vid = td.vid');
    $query->condition('status', '1', '=');
    $query->condition('td.tid', '49', '=');
    return $query;
  }
}

/**
 * Catalog Entry mappings and handling
 */
class d6d7OfficialServiceMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the IT division - a simple text list
    $this->addFieldMapping('field_it_services_division', 'field_service_department');

    // Map the various owners
    $this->addFieldMapping('field_owner',            'field_service_business_owner');
    $this->addFieldMapping('field_service_owner',    'field_service_technical_owner');
    $this->addFieldMapping('field_operations_owner', 'field_service_operations_owner');
    $this->addFieldMapping('field_service_manager',  'field_service_manager');

    // TODO: Map the service page
    $this->addFieldMapping('field_service_page','nid');

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid')->callbacks(array($this, 'calcID'));
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    // don't import the path, we want the new IDs since the paths
    // point to the service pages
    $this->removeFieldMapping('path');
  }

  // This function adds 20000 to the node ID to avoid conflicts since this
  // is a new content type (for other nodes, we'll likely keep the same ID
  protected function calcID($value) {
    $value = $value + 20000;
    return $value;
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');
    return $query;
  }
}

/**
 * Catalog Entry mappings and handling
 */
class d6d7ServicePageMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Overview
    $this->addFieldMapping('field_service_overview', 'field_service_introduction');
    $this->addFieldMapping('field_service_overview:format')->defaultValue('full_html');

    // Body
    $this->addFieldMapping('body', 'merged_features');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
 
    // Getting Started
    $this->addFieldMapping('field_service_getting_started', 'merged_getting_started');
    $this->addFieldMapping('field_service_getting_started:format')->defaultValue('full_html');

	// Service Information
	$this->addFieldMapping('field_service_information', 'merged_service_information');
    $this->addFieldMapping('field_service_information:format')->defaultValue('full_html');

    // Notice
	$this->addFieldMapping('field_service_notice', 'merged_notice');
    $this->addFieldMapping('field_service_notice:format')->defaultValue('full_html');

    // Create a node with the same ID
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

	// FAQ Links
	$this->addFieldMapping('field_service_faq_links','field_service_url_faq');
	$this->addFieldMapping('field_service_faq_links:title','field_service_url_faq:title');
	$this->addFieldMapping('field_service_faq_links:attributes','field_service_url_faq:attributes');

	// Support Links
	$this->addFieldMapping('field_service_support_links','field_service_url_support');
	$this->addFieldMapping('field_service_support_links:title','field_service_url_support:title');
	$this->addFieldMapping('field_service_support_links:attributes','field_service_url_support:attributes');

	// Launch Links
	$this->addFieldMapping('field_service_launch_links','field_service_url_launch');
	$this->addFieldMapping('field_service_launch_links:title','field_service_url_launch:title');
	$this->addFieldMapping('field_service_launch_links:attributes','field_service_url_launch:attributes');

    // Order Links
	$this->addFieldMapping('field_service_order_links','field_service_url_order');
	$this->addFieldMapping('field_service_order_links:title','field_service_url_order:title');
	$this->addFieldMapping('field_service_order_links:attributes','field_service_url_order:attributes');

    // Related Links
	$this->addFieldMapping('field_service_related_links','field_service_url_related');
	$this->addFieldMapping('field_service_related_links:title','field_service_url_related:title');
	$this->addFieldMapping('field_service_related_links:attributes','field_service_url_related:attributes');

    // Related Links
	$this->addFieldMapping('field_service_request_links','field_service_url_request');
	$this->addFieldMapping('field_service_request_links:title','field_service_url_request:title');
	$this->addFieldMapping('field_service_request_links:attributes','field_service_url_request:attributes');

    // Download Links
	$this->addFieldMapping('field_service_download_links','field_service_url_download');
	$this->addFieldMapping('field_service_download_links:title','field_service_url_download:title');
	$this->addFieldMapping('field_service_download_links:attributes','field_service_url_download:attributes');

    $this->addFieldMapping('field_service_related_services','field_service_related_services');

    // Unmapped destination fields
    $this->addFieldMapping('body:summary', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
    $this->addFieldMapping('field_service_overview:language', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
    $this->addFieldMapping('field_service_getting_started:language', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));

    // Unmapped source fields
	$merged_fields = array(
	  'body',
	  'teaser',
      'field_service_acq_summary',
      'field_service_acq_details',
	  'field_service_availableto',
      'field_service_requirements',
      'field_service_security_summary',
      'field_service_security_details',
      'field_service_support_summary',
      'field_service_support_details',
      'field_service_cost',
	  // Features Section
	  'field_service_features_summary',
	  'field_service_features_details',
	  'field_service_tiers',
	  'field_service_examples_summary',
	  'field_service_examples_details',
	  'field_service_notice',
	  'field_service_side_notice',
    );

	$ignored_fields = array(
	  // ignoring the terms
	  '1',
	  '2',
	  '3',
	  '4',
	  '5',
      // managed by Official Service
      'field_service_operations_owner',
      'field_service_manager',
      'field_service_business_owner',
      'field_service_technical_owner',
      // never used
      'field_service_reviewer',
      // roles and responsibilities is part of service description
      'field_service_roles',
      'field_service_roles:format',
      // Table of contents not used
      'field_service_toc',
	  // Vanity Links not used
      'field_service_url_vanity',
	  'field_service_url_vanity:title',
	  'field_service_url_vanity:attributes',
	  // Status Link not used
	  'field_service_url_status',
	  'field_service_url_status:title',
	  'field_service_url_status:attributes',
	  // Information Links not used in this class
	  'field_service_url_information',
	  'field_service_url_information:title',
	  'field_service_url_information:attributes',
	  // Parent service not used
	  'field_service_parent',
	  // Service Catalog is moved in another class
	  'field_service_catalog',
	  'field_service_catalog:format',
	  'field_service_catalog_title',
	  // Charge not used
	  'field_service_charge',
	  // Business notes not used (and would not be in this class anyway)
	  'field_service_notes',
	  'field_service_notes:format',
	  'field_service_availableto:format',
      'field_service_acq_summary:format',
      'field_service_acq_details:format',
      'field_service_introduction:format',
      'field_service_internal',
      'field_service_internal:format',
      'field_service_images',
      'field_service_images:list',
      'field_service_images:data',
      'field_service_information:format',
      'field_service_requirements:format',
      'field_service_security_class',
      'field_service_security_details:format',
      'field_service_security_summary:format',
      'field_service_support_summary:format',
      'field_service_support_details:format',
      'field_service_cost:format',
	  'field_service_tiers:format',
	  'field_service_features_summary:format',
	  'field_service_features_details:format',
	  'field_service_examples_summary:format',
	  'field_service_examples_details:format',
	  'field_service_notice:format',
	  'field_service_side_notice:format',
	  'format',
	  // Concierge not needed on service page
	  'field_service_concierge',
	  // Service Department handled by another class
	  'field_service_department',
    );

	foreach ($ignored_fields as $ignored_field) {
      $this->addFieldMapping(NULL, $ignored_field)->issueGroup(t('DNM'))->description(t('Ignored'));
	}

    foreach ($merged_fields as $merged_field) {
      $this->addFieldMapping(NULL, $merged_field)->issueGroup(t('DNM'))->description(t('Merged'));
	}
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');

    // Join summary / details fields
    // See: http://drupal.org/node/1012810
    $query->addExpression('CONCAT_WS(\'\',f.field_service_acq_summary_value, f.field_service_acq_details_value)', 'merged_getting_started');

    // Side and Top Notice 
	// this one sets the example to NULL instaed of ''
    $query->addExpression('IF( length( CONCAT_WS(\'\',f.field_service_notice_value, f.field_service_side_notice_value)), CONCAT_WS(\'\',f.field_service_notice_value, f.field_service_side_notice_value), NULL)', 'merged_notice');

	// Features Section
    $query->addExpression('CONCAT_WS(\'\',body, f.field_service_features_summary_value, f.field_service_features_details_value' . ', '
	  . d6d7_build_expression('Service Tiers', 'f.field_service_tiers_value') . ', '
	  . d6d7_build_expression('How to Use', 'f.field_service_examples_summary_value', 'f.field_service_examples_details_value') . ')'
	  , 'merged_features');

	// Service Information Section
    $query->addExpression('CONCAT_WS(\'\',' 
	  . d6d7_build_expression('Available To',  'f.field_service_availableto_value') . ', '
      . d6d7_build_expression('Requirements',  'f.field_service_requirements_value') . ', '
	  . d6d7_build_expression('Data Security', 'f.field_service_security_summary_value', 'f.field_service_security_details_value') . ', '
	  . d6d7_build_expression('Support',       'f.field_service_support_summary_value', 'f.field_service_support_details_value') . ', '
	  . d6d7_build_expression('Rates',         'f.field_service_cost_value') . ')'
      , 'merged_service_information');
    return $query;
  }
}

function d6d7_build_expression($title, $first_field, $second_field = '') {
  if ($second_field != '') {
    $sub_expression = "CONCAT_WS('',$first_field, $second_field)";
  }
  else {
    $sub_expression = $first_field;
  }
  $expression = "CONCAT('<h3>$title</h3>', IF( length( $sub_expression) , $sub_expression, NULL))";
  return $expression;
}

/**
   * Implementation of Migration::prepareRow().
   *
   * Here we pull in additional data from a non-core, non-CCK table.
   *
   * @param $row
   */
/*
  public function prepareRow($row) { if (parent::prepareRow($row) === FALSE) { return FALSE; } $image_row = Database::getConnection('default', $this->sourceConnection) ->select('custom_image_table', 'i') ->fields('i', array('copyright', 'filename')) ->condition('vid', $row->vid) ->execute()
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
