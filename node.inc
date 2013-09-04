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
 *  Agreements
 */

class d6d7AgreementsMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_agreement_calendar', 'field_sla_calendar');
    $this->addFieldMapping('field_agreement_calendar:format')->defaultValue('full_html');
    $this->addFieldMapping('field_agreement_calendar:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_agreement_contact', 'field_sla_contact');
    $this->addFieldMapping('field_agreement_contact:format')->defaultValue('full_html');
    $this->addFieldMapping('field_agreement_contact:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_agreement_exceptions', 'field_sla_exceptions');
    $this->addFieldMapping('field_agreement_exceptions:format')->defaultValue('full_html');
    $this->addFieldMapping('field_agreement_exceptions:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_agreement_add_services', 'field_sla_additional_services');
    $this->addFieldMapping('field_agreement_add_services:format')->defaultValue('full_html');
    $this->addFieldMapping('field_agreement_add_services:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_agreement_services', 'field_sla_services')->callbacks(array($this, 'calcID'));

    $this->addUnmigratedSources(array(
      'field_sla_calendar:format',
      'field_sla_contact:format',
      'field_sla_exceptions:format',
      'field_sla_additional_services:format',
    ));
  }

  // This function adds 20000 to the node ID
  // The Official Service IDs have the old service IDs + 20000
  protected function calcID($data) {

    // This will be an array of IDs
    $new_data = array();

    foreach ($data as $key => $value) {
      if ($value) {
        $value = $value + 20000;
      }
      $new_data[$key] = $value;
    }
    return $new_data;
  }
}

/**
 *  Announcements
 */

class d6d7AnnouncementsMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_date', 'field_news_date');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue(LANGUAGE_NONE);

    $this->addUnmigratedSources(array(
      'field_news_concierge',
      'field_news_images',
      'field_news_images:list',
      'field_news_images:data',
      'field_news_services',
      'field_news_location',
      'format',
    ));
  }


  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');
    $query->join('content_field_news_location', 'loc', 'n.vid = loc.vid');
    $query->condition('status', '1', '=');
    $query->condition('loc.field_news_location_value', 'IT Services Home Page', '=');

    return $query;
  }
}

/**
 *  HelpSU News
 */

class d6d7NewsMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_date', 'field_news_date');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue(LANGUAGE_NONE);

    $this->addUnmigratedSources(array(
      'field_news_concierge',
      'field_news_images',
      'field_news_images:list',
      'field_news_images:data',
      'field_news_services',
      'field_news_location',
      'format',
    ));
  }


  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');
    $query->join('content_field_news_location', 'loc', 'n.vid = loc.vid');
    $query->condition('status', '1', '=');
    $query->condition('loc.field_news_location_value', 'HelpSU', '=');

    return $query;
  }
}
 
/**
 *  Technology Strategy
 */

class d6d7TechStrategyMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');

    // Body
    $this->addFieldMapping('body', 'merged_strategy');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_old_content_type')->defaultValue('techstrategy');
    $this->addFieldMapping('field_old_content_type:create_term')->defaultValue('TRUE');

    $this->addFieldMapping('field_services', 'field_techstrategy_services');
    $this->addFieldMapping('field_related_pages', 'field_techstrategy_strategies');

    $this->addUnmigratedSources(array(
      'field_techstrategy_toc',
      'format',
      'field_techstrategy_vision',
      'field_techstrategy_vision:format',
      'field_techstrategy_overview',
      'field_techstrategy_overview:format',
      'field_techstrategy_currentstate',
      'field_techstrategy_currentstate:format',
      'field_techstrategy_images',
      'field_techstrategy_images:list',
      'field_techstrategy_images:data',
      'body',
    ));

    $this->addUnmigratedDestinations(array(
      'field_files',
      'field_files:file_class',
      'field_files:language',
      'field_files:preserve_files',
      'field_files:destination_dir',
      'field_files:destination_file',
      'field_files:file_replace',
      'field_files:source_dir',
      'field_files:description',
      'field_files:display',
      'field_old_content_type:source_type',
      'field_old_content_type:ignore_case',
    ));
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');

    // Body
    $query->addExpression('CONCAT_WS(\'\','
      . d6d7_build_expression('Overview',      'f.field_techstrategy_overview_value',     '', 'h2') . ', '
      . d6d7_build_expression('Current State', 'f.field_techstrategy_currentstate_value', '', 'h2') . ', '
      . d6d7_build_expression('Vision',        'f.field_techstrategy_vision_value',       '', 'h2') . ')'
      , 'merged_strategy');
    return $query;
  }
}

/**
 *  Technology Strategy Category
 */

class d6d7TechStrategyCategoryMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_old_content_type')->defaultValue('techstrategycat');
    $this->addFieldMapping('field_old_content_type:create_term')->defaultValue('TRUE');

    $this->addUnmigratedSources(array(
      'format',
    ));

    $this->addUnmigratedDestinations(array(
      'field_files',
      'field_files:file_class',
      'field_files:language',
      'field_files:preserve_files',
      'field_files:destination_dir',
      'field_files:destination_file',
      'field_files:file_replace',
      'field_files:source_dir',
      'field_files:description',
      'field_files:display',
      'field_old_content_type:source_type',
      'field_old_content_type:ignore_case',
    ));
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
 *  Static Page
 */

class d6d7StaticPageMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_old_content_type')->defaultValue('static');
    $this->addFieldMapping('field_old_content_type:create_term')->defaultValue('TRUE');

    $this->addUnmigratedSources(array(
      'field_static_code',
      'field_static_code:format',
      'field_static_files',
      'field_static_files:list',
      'field_static_files:data',
      'field_static_images',
      'field_static_images:list',
      'field_static_images:data',
      'field_static_internal',
      'field_static_internal:format',
      'field_static_notice',
      'field_static_notice:format',
      'format',
    ));
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');
    // home page
    $query->condition('n.nid', '1079', '!=');
    // services
    $query->condition('n.nid', '3600', '!=');
    // service owners view
    $query->condition('n.nid', '3132', '!=');
    // status definitions
    $query->condition('n.nid', '2711', '!=');
    // 404 and 403 pages
    $query->condition('n.nid', '2205', '!=');
    $query->condition('n.nid', '2207', '!=');
    return $query;
  }
}


/**
 *  Organization Migration
 */
class d6d7OrganizationMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_files', 'field_organization_files')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_files:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_files:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_files:language')->defaultValue(LANGUAGE_NONE);

    $this->addUnmigratedSources(array(
      // Images are not used by this content type
      'field_organization_images',
      'field_organization_images:list',
      'field_organization_images:data',
      // These fields aren't needed
      'field_organization_files:list',
      'field_organization_files:data',
      // format set to full_html
      'format',
    ));

    $this->addUnmigratedDestinations(array(
      'field_files:description',
      'field_files:display',
      'field_old_content_type:source_type',
      'field_old_content_type:ignore_case',
    ));

    $this->addFieldMapping('field_old_content_type')->defaultValue('organization');
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
 *  Group Migration
 */
class d6d7GroupMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addUnmigratedSources(array(
      // Images are not used by this content type
      'field_group_images',
      'field_group_images:list',
      'field_group_images:data',
      // These fields aren't needed
      'field_group_files',
      'field_group_files:list',
      'field_group_files:data',
      // format set to full_html
      'format',
    ));

    $this->addFieldMapping('field_old_content_type')->defaultValue('group');
    $this->addFieldMapping('field_old_content_type:create_term')->defaultValue('TRUE');
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
 *  Media Migration
 */
class d6d7MediaMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');

    $this->addFieldMapping('field_information_files', 'field_media_files');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_old_content_type')->defaultValue('media');
    $this->addFieldMapping('field_old_content_type:create_term')->defaultValue('TRUE');

    $this->addUnmigratedSources(array(
      // Images are not used by this content type
      'field_media_images',
      'field_media_images:list',
      'field_media_images:data',
      // These fields aren't needed
      'field_media_files:list',
      'field_media_files:data',
      // format set to full_html
      'format',
    ));

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
 *  Service Description Migration
 */
class d6d7DescriptionMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Map the node ID to the existing ID, but first pass it through the calcID function
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    $this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('field_description_service', 'field_description_services')->callbacks(array($this, 'calcID'));
	
	$fields = array(
	  'field_description_overview',
	  'field_description_documentation',
	  'field_description_installation',
	  'field_description_monitoring',
	  'field_description_planning',
	  'field_description_responsibility',
	  'field_description_security',
	  'field_description_support'
	);

	$this->addSimpleMappings($fields);

	foreach ($fields as $field) {
	  $this->addFieldMapping($field . ':format')->defaultValue('full_html');
	  $this->addFieldMapping(NULL, $field . ':format')->issueGroup(t('DNM'))->description(t('Ignored'));
	}

	foreach ($fields as $field) {
	  $this->addFieldMapping($field . ':language', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
    }

  }

  protected function calcID($value) {
    $value = $value + 20000;
    return $value;
  }
}

/**
 * Catalog Entry mappings and handling
 */
class d6d7CatalogEntryMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

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

    // Set the Service Provider to IT Services
	$this->addFieldMapping('field_catalog_service_provider')->defaultValue('Information Technology Services');

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

class d6d7OtherProviderCatalogEntryMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

    // map the service catalog content to the body
    $this->addFieldMapping('body', 'field_otherservice_catalog');

    // setting the format of the body to full_html
    // had to change the content type to accept user-provided formats
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    // don't import the path, we want the new IDs since the paths
    // point to the service pages
    $this->removeFieldMapping('path');

    // Map the catalog category to this field, and use the tid to make the match
    $this->addFieldMapping('field_catalog_entry_categories', 1);
    $this->addFieldMapping('field_catalog_entry_categories:source_type')->defaultValue('tid');

    // Map the service provider to this field, and use the tid to make the match
    $this->addFieldMapping('field_catalog_service_provider', 3);
    $this->addFieldMapping('field_catalog_service_provider:source_type')->defaultValue('tid');

    // Links
    $this->addFieldMapping('field_catalog_entry_link', 'field_otherservice_url');
    $this->addFieldMapping('field_catalog_entry_link:title', 'field_otherservice_url:title');

    $this->addUnmigratedDestinations(array(
      'field_catalog_entry_categories:create_term',
      'field_catalog_entry_categories:ignore_case',
      'field_catalog_service_provider:create_term',
      'field_catalog_service_provider:ignore_case',
      'field_catalog_entry_link:attributes',
      'field_catalog_entry_link:language',
      'path',
    ));

    $this->addUnmigratedSources(array(
      'field_otherservice_catalog:format',
      'path',
      '2',
      'field_otherservice_url:attributes',
      '5',
      'body',
      '4',
      'format',
    ));


    // Set the Service Provider to IT Services
//    $this->addFieldMapping('field_catalog_service_provider')->defaultValue('Information Technology Services');

    // Destination fields ignored
//    $this->addFieldMapping('field_catalog_entry_link:title', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
//    $this->addFieldMapping('field_catalog_entry_link:attributes', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
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
 * Official Service mappings and handling
 */
class d6d7OfficialServiceMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

    // Map the IT division - a simple text list
    $this->addFieldMapping('field_official_division', 'field_service_department');

    // Map the various owners
    $this->addFieldMapping('field_official_owner',            'field_service_business_owner');
    $this->addFieldMapping('field_official_service_owner',    'field_service_technical_owner');
    $this->addFieldMapping('field_official_operations_owner', 'field_service_operations_owner');
    $this->addFieldMapping('field_official_service_manager',  'field_service_manager');

    // Map the service page
    $this->addFieldMapping('field_service','nid');

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
 * Service Page mappings and handling
 */
class d6d7ServicePageMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

    // Overview
    $this->addFieldMapping('field_service_overview', 'field_service_introduction');
    $this->addFieldMapping('field_service_overview:format')->defaultValue('full_html');
    $this->addFieldMapping('field_service_overview:language')->defaultValue(LANGUAGE_NONE);

    // Body
    $this->addFieldMapping('body', 'merged_features');
    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('body:language')->defaultValue(LANGUAGE_NONE);
 
	// Service Information
	$this->addFieldMapping('field_service_information', 'merged_service_information');
    $this->addFieldMapping('field_service_information:format')->defaultValue('full_html');
    $this->addFieldMapping('field_service_information:language')->defaultValue(LANGUAGE_NONE);

    // Notice
	$this->addFieldMapping('field_service_notice', 'merged_notice');
    $this->addFieldMapping('field_service_notice:format')->defaultValue('full_html');
    $this->addFieldMapping('field_service_notice:language')->defaultValue(LANGUAGE_NONE);

    // Create a node with the same ID
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

	// FAQ Links
	$this->addFieldMapping('field_service_faq_links','field_service_url_faq');
	$this->addFieldMapping('field_service_faq_links:title','field_service_url_faq:title');
	$this->addFieldMapping('field_service_faq_links:attributes','field_service_url_faq:attributes');
	$this->addFieldMapping('field_service_faq_links:language')->defaultValue(LANGUAGE_NONE);

	// Support Links
	$this->addFieldMapping('field_service_support_links','field_service_url_support');
	$this->addFieldMapping('field_service_support_links:title','field_service_url_support:title');
	$this->addFieldMapping('field_service_support_links:attributes','field_service_url_support:attributes');
	$this->addFieldMapping('field_service_support_links:language')->defaultValue(LANGUAGE_NONE);

	// Launch Links
	$this->addFieldMapping('field_service_launch_links','field_service_url_launch');
	$this->addFieldMapping('field_service_launch_links:title','field_service_url_launch:title');
	$this->addFieldMapping('field_service_launch_links:attributes','field_service_url_launch:attributes');
	$this->addFieldMapping('field_service_launch_links:language')->defaultValue(LANGUAGE_NONE);

    // Order Links
	$this->addFieldMapping('field_service_order_links','field_service_url_order');
	$this->addFieldMapping('field_service_order_links:title','field_service_url_order:title');
	$this->addFieldMapping('field_service_order_links:attributes','field_service_url_order:attributes');
	$this->addFieldMapping('field_service_order_links:language')->defaultValue(LANGUAGE_NONE);

    // Related Links
	$this->addFieldMapping('field_service_related_links','field_service_url_related');
	$this->addFieldMapping('field_service_related_links:title','field_service_url_related:title');
	$this->addFieldMapping('field_service_related_links:attributes','field_service_url_related:attributes');
	$this->addFieldMapping('field_service_related_links:language')->defaultValue(LANGUAGE_NONE);

    // Related Links
	$this->addFieldMapping('field_service_request_links','field_service_url_request');
	$this->addFieldMapping('field_service_request_links:title','field_service_url_request:title');
	$this->addFieldMapping('field_service_request_links:attributes','field_service_url_request:attributes');
	$this->addFieldMapping('field_service_request_links:language')->defaultValue(LANGUAGE_NONE);

    // Download Links
	$this->addFieldMapping('field_service_download_links','field_service_url_download');
	$this->addFieldMapping('field_service_download_links:title','field_service_url_download:title');
	$this->addFieldMapping('field_service_download_links:attributes','field_service_url_download:attributes');
	$this->addFieldMapping('field_service_download_links:language')->defaultValue(LANGUAGE_NONE);

    $this->addFieldMapping('field_services','field_service_related_services');

    $this->addFieldMapping('field_service_files', 'field_service_files')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_service_files:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_service_files:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_service_files:language')->defaultValue(LANGUAGE_NONE);
	

    // Unmapped destination fields
    $this->addFieldMapping('body:summary', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
    $this->addFieldMapping('field_service_files:description', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
    $this->addFieldMapping('field_service_files:display', NULL)->issueGroup(t('DNM'))->description(t('Ignored'));
	// New fields
    $this->addFieldMapping('field_service_for_it_providers', NULL)->issueGroup(t('DNM'))->description(t('New'));
    $this->addFieldMapping('field_service_for_it_providers:format', NULL)->issueGroup(t('DNM'))->description(t('New'));
    $this->addFieldMapping('field_service_for_it_providers:language', NULL)->issueGroup(t('DNM'))->description(t('New'));
    $this->addFieldMapping('field_service_instructions', NULL)->issueGroup(t('DNM'))->description(t('New'));
    $this->addFieldMapping('field_service_instructions:format', NULL)->issueGroup(t('DNM'))->description(t('New'));
    $this->addFieldMapping('field_service_instructions:language', NULL)->issueGroup(t('DNM'))->description(t('New'));

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
	  'field_service_files:list',
	  'field_service_files:data',
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

    // Side and Top Notice 
	// this one sets the example to NULL instaed of ''
    $query->addExpression('IF( length( CONCAT_WS(\'\',f.field_service_notice_value, f.field_service_side_notice_value)), CONCAT_WS(\'\',f.field_service_notice_value, f.field_service_side_notice_value), NULL)', 'merged_notice');

	// Features Section
    $query->addExpression('CONCAT_WS(\'\',body, f.field_service_features_summary_value, f.field_service_features_details_value' . ', '
	  . d6d7_build_expression('Service Tiers', 'f.field_service_tiers_value') . ', '
	  . d6d7_build_expression('How to Use', 'f.field_service_examples_summary_value', 'f.field_service_examples_details_value') . ', '
      . d6d7_build_expression('Getting Started', 'f.field_service_acq_summary_value', 'f.field_service_acq_details_value') . ')'
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

/**
 * Topic Page mappings and handling
 */
class d6d7TopicMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

    // Create a node with the same ID
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    //  $this->addFieldMapping('field_information_services', 'field_concierge_services');

    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

    // Files
    $this->addFieldMapping('field_guide_files', 'field_concierge_files')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_guide_files:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_guide_files:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_guide_files:language')->defaultValue(LANGUAGE_NONE);

    // Images
    // Preserve Images on Rollback
    $this->addFieldMapping('field_guide_images:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_guide_files:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_guide_images:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_guide_images:language')->defaultValue(LANGUAGE_NONE);

    //$this->addFieldMapping('field_guide_images:alt', 'field_details_images:data')->callbacks(array($this, 'd6d7_get_alt'));;
   // $this->addFieldMapping('field_guide_images', 'field_concierge_c1_image')->sourceMigration('FileMigration');
    //$this->addFieldMapping('field_guide_images', 'field_concierge_c2_image')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_guide_images', 'all_images')->sourceMigration('FileMigration');

    $this->addUnmigratedDestinations(array(
      'field_guide_images:alt',
      'field_guide_images:title',
      )
    );
    $this->addUnmigratedSources(array(
	  // Leave service relationships out for now
	  'field_concierge_services',
      // images are merged together
      'field_concierge_c1_image',
      'field_concierge_c1_image:list',
      'field_concierge_c1_image:data',
      'field_concierge_c2_image',
      'field_concierge_c2_image:list',
      'field_concierge_c2_image:data',
      'field_concierge_c3_image',
      'field_concierge_c3_image:list',
      'field_concierge_c3_image:data',
      'field_concierge_c4_image',
      'field_concierge_c4_image:list',
      'field_concierge_c4_image:data',
      'field_concierge_c5_image',
      'field_concierge_c5_image:list',
      'field_concierge_c5_image:data',
      'field_concierge_c6_image',
      'field_concierge_c6_image:list',
      'field_concierge_c6_image:data',
      'field_concierge_c7_image',
      'field_concierge_c7_image:list',
      'field_concierge_c7_image:data',
      // Files
      'field_concierge_files:list',
      'field_concierge_files:data',
      // Rest of fields
      'field_concierge_c7_content',
      'field_concierge_c7_content:format',
      'field_concierge_c2_custom',
      'field_concierge_c2_custom:format',
      'field_concierge_c3_custom',
      'field_concierge_c3_custom:format',
      'field_concierge_c4_custom',
      'field_concierge_c4_custom:format',
      'field_concierge_c5_custom',
      'field_concierge_c5_custom:format',
      'field_concierge_c6_custom',
      'field_concierge_c6_custom:format',
      'field_concierge_c7_custom',
      'field_concierge_c7_custom:format',
      // weights (unused)
      'field_concierge_c1_weight',
      'field_concierge_c2_weight',
      'field_concierge_c3_weight',
      'field_concierge_c4_weight',
      'field_concierge_c5_weight',
      'field_concierge_c6_weight',
      'field_concierge_c7_weight',
      'field_concierge_l1_weight',
      'field_concierge_l2_weight',
      'field_concierge_l3_weight',
      'field_concierge_l4_weight',
      'field_concierge_l5_weight',
      'field_concierge_r1_weight',
      'field_concierge_r2_weight',
      'field_concierge_r3_weight',
      'field_concierge_r4_weight',
      'field_concierge_r5_weight',
      // vanity URL
      'field_concierge_url_vanity',
      'field_concierge_url_vanity:title',
      'field_concierge_url_vanity:attributes',
      // Main and Side Notice (empty)
      'field_concierge_notice',
      'field_concierge_notice:format',
      'field_concierge_side_notice',
      'field_concierge_side_notice:format',
      // Service Category
      'field_concierge_service_category',
      '1',
      // Images (not empty, but not used)
      'field_concierge_images',
      'field_concierge_images:list',
      'field_concierge_images:data',
      // Center #2 parts not used
      'field_concierge_c1_url',
      'field_concierge_c1_url:title',
      'field_concierge_c1_url:attributes',
      // Center #2 parts not used
      'field_concierge_c2_url',
      'field_concierge_c2_url:title',
      'field_concierge_c2_url:attributes',
      // Center #3 parts not used
      'field_concierge_c3_url',
      'field_concierge_c3_url:title',
      'field_concierge_c3_url:attributes',
      // Center #4 parts not used
      'field_concierge_c4_url',
      'field_concierge_c4_url:title',
      'field_concierge_c4_url:attributes',
      // Center #5 parts not used
      'field_concierge_c5_url',
      'field_concierge_c5_url:title',
      'field_concierge_c5_url:attributes',
      // Center #6 parts not used
      'field_concierge_c6_url',
      'field_concierge_c6_url:title',
      'field_concierge_c6_url:attributes',
      // Center #7 (not used)
      'field_concierge_c7_description',
      'field_concierge_c7_description:format',
      'field_concierge_c7_heading',
      'field_concierge_c7_image',
      'field_concierge_c7_image:list',
      'field_concierge_c7_image:data',
      'field_concierge_c7_url',
      'field_concierge_c7_url:title',
      'field_concierge_c7_url:attributes',
      // Left Field #1 parts not used
      'field_concierge_l1_custom',
      'field_concierge_l1_custom:format',
      'field_concierge_l1_url',
      'field_concierge_l1_url:title',
      'field_concierge_l1_url:attributes',
      // Left Field #2 parts not used
      'field_concierge_l2_custom',
      'field_concierge_l2_custom:format',
      'field_concierge_l2_url',
      'field_concierge_l2_url:title',
      'field_concierge_l2_url:attributes',
      // Left Field #3 parts not used
      'field_concierge_l3_custom',
      'field_concierge_l3_custom:format',
      'field_concierge_l3_url',
      'field_concierge_l3_url:title',
      'field_concierge_l3_url:attributes',
      // Left Field #4 not used
      'field_concierge_l4_content',
      // Center #6 parts not used
      'field_concierge_c6_url',
      'field_concierge_c6_url:title',
      'field_concierge_c6_url:attributes',
      // Center #7 (not used)
      'field_concierge_c7_description',
      'field_concierge_c7_description:format',
      'field_concierge_c7_heading',
      'field_concierge_c7_image',
      'field_concierge_c7_image:list',
      'field_concierge_c7_image:data',
      'field_concierge_c7_url',
      'field_concierge_c7_url:title',
      'field_concierge_c7_url:attributes',
      // Left Field #1 parts not used
      'field_concierge_l1_custom',
      'field_concierge_l1_custom:format',
      'field_concierge_l1_url',
      'field_concierge_l1_url:title',
      'field_concierge_l1_url:attributes',
      // Left Field #2 parts not used
      'field_concierge_l2_custom',
      'field_concierge_l2_custom:format',
      'field_concierge_l2_url',
      'field_concierge_l2_url:title',
      'field_concierge_l2_url:attributes',
      // Left Field #3 parts not used
      'field_concierge_l3_custom',
      'field_concierge_l3_custom:format',
      'field_concierge_l3_url',
      'field_concierge_l3_url:title',
      'field_concierge_l3_url:attributes',
      // Left Field #4 not used
      'field_concierge_l4_content',
      'field_concierge_l4_content:format',
      'field_concierge_l4_custom',
      'field_concierge_l4_custom:format',
      'field_concierge_l4_heading',
      'field_concierge_l4_icon',
      'field_concierge_l4_url',
      'field_concierge_l4_url:title',
      'field_concierge_l4_url:attributes',
      // Left Field #5 not used
      'field_concierge_l5_content',
      'field_concierge_l5_content:format',
      'field_concierge_l5_custom',
      'field_concierge_l5_custom:format',
      'field_concierge_l5_heading',
      'field_concierge_l5_icon',
      'field_concierge_l5_url',
      'field_concierge_l5_url:title',
      'field_concierge_l5_url:attributes',
      // Right Field #1 parts not used
      'field_concierge_r1_custom',
      'field_concierge_r1_custom:format',
      'field_concierge_r1_url',
      'field_concierge_r1_url:title',   
      'field_concierge_r1_url:attributes',
      // Right Field #2 parts not used
      'field_concierge_r2_custom',
      'field_concierge_r2_custom:format',
      'field_concierge_r2_url',
      'field_concierge_r2_url:title',   
      'field_concierge_r2_url:attributes',
      // Right Field #3 parts not used
      'field_concierge_r3_custom',
      'field_concierge_r3_custom:format',
      'field_concierge_r3_url',
      'field_concierge_r3_url:title',   
      'field_concierge_r3_url:attributes',
      // Right Field #4 not used
      'field_concierge_r4_content',
      'field_concierge_r4_content:format',
      'field_concierge_r4_custom',
      'field_concierge_r4_custom:format',   
      'field_concierge_r4_heading', 
      'field_concierge_r4_icon',
      'field_concierge_r4_url',
      'field_concierge_r4_url:title',   
      'field_concierge_r4_url:attributes',
      // Right Field #5 not used
      'field_concierge_r5_content',
      'field_concierge_r5_content:format',
      'field_concierge_r5_custom',
      'field_concierge_r5_custom:format',
      'field_concierge_r5_heading',
      'field_concierge_r5_icon',
      'field_concierge_r5_url',
      'field_concierge_r5_url:title',
      'field_concierge_r5_url:attributes',

      // Merged
      'field_concierge_c1_image', 
      'field_concierge_c2_image', 
      'field_concierge_c3_image', 
      'field_concierge_c4_image', 
      'field_concierge_c5_image', 
      'field_concierge_c6_image', 

      // Content
      'field_concierge_c1_custom',
      'field_concierge_c1_custom:format',
      'field_concierge_c1_heading',
      'field_concierge_c1_content',
      'field_concierge_c1_content:format',
      'field_concierge_c1_description',
      'field_concierge_c1_description:format',
      'field_concierge_c1_image',

      'field_concierge_c2_heading',
      'field_concierge_c2_content',
      'field_concierge_c2_content:format',
      'field_concierge_c2_description',
      'field_concierge_c2_description:format',
      'field_concierge_c2_image',

      'field_concierge_c3_heading',
      'field_concierge_c3_content',
      'field_concierge_c3_content:format',
      'field_concierge_c3_description',
      'field_concierge_c3_description:format',
      'field_concierge_c3_image',

      'field_concierge_c4_heading',
      'field_concierge_c4_content',
      'field_concierge_c4_content:format',
      'field_concierge_c4_description',
      'field_concierge_c4_description:format',
      'field_concierge_c4_image',

      'field_concierge_c5_heading',
      'field_concierge_c5_content',
      'field_concierge_c5_content:format',
      'field_concierge_c5_description',
      'field_concierge_c5_description:format',
      'field_concierge_c5_image',

      'field_concierge_c6_heading',
      'field_concierge_c6_content',
      'field_concierge_c6_content:format',
      'field_concierge_c6_description',
      'field_concierge_c6_description:format',
      'field_concierge_c6_image',

      'field_concierge_c7_heading',
      'field_concierge_c7_content',
      'field_concierge_c7_content:format',
      'field_concierge_c7_description',
      'field_concierge_c7_description:format',
      'field_concierge_c7_image',

      'field_concierge_l1_heading',
      'field_concierge_l1_content',
      'field_concierge_l1_content:format',
      'field_concierge_l1_icon',

      'field_concierge_l2_heading',
      'field_concierge_l2_content',
      'field_concierge_l2_content:format',
      'field_concierge_l2_icon',

      'field_concierge_l3_heading',
      'field_concierge_l3_content',
      'field_concierge_l3_content:format',
      'field_concierge_l3_icon',

      'field_concierge_l4_heading',
      'field_concierge_l4_content',
      'field_concierge_l4_icon',

      'field_concierge_l5_heading',
      'field_concierge_l5_content',
      'field_concierge_l5_icon',

      'field_concierge_r1_heading',
      'field_concierge_r1_content',
      'field_concierge_r1_content:format',
      'field_concierge_r1_icon',
      
      'field_concierge_r2_heading',
      'field_concierge_r2_content',
      'field_concierge_r2_content:format',
      'field_concierge_r2_icon',
      
      'field_concierge_r3_heading',
      'field_concierge_r3_content',
      'field_concierge_r3_content:format',
      'field_concierge_r3_icon',
      
      'field_concierge_r4_heading',
      'field_concierge_r4_content',
      'field_concierge_r4_icon',
      
      'field_concierge_r5_heading',
      'field_concierge_r5_content',
      'field_concierge_r5_icon',
      )
    );
  }

  public function prepareRow($row) {

    parent::prepareRow($row);

    $row->all_images[] = $row->field_concierge_c1_image;
    $row->all_images[] = $row->field_concierge_c2_image;
    $row->all_images[] = $row->field_concierge_c3_image;
    $row->all_images[] = $row->field_concierge_c4_image;
    $row->all_images[] = $row->field_concierge_c5_image;
    $row->all_images[] = $row->field_concierge_c6_image;

    
    $content .= '<div class="span3">';

    $content .= $this->build_side_card(
      $row->field_concierge_l1_heading,
      $row->field_concierge_l1_content,
      $row->field_concierge_l1_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_l2_heading,
      $row->field_concierge_l2_content,
      $row->field_concierge_l2_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_l3_heading,
      $row->field_concierge_l3_content,
      $row->field_concierge_l3_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_l4_heading,
      $row->field_concierge_l4_content,
      $row->field_concierge_l4_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_l5_heading,
      $row->field_concierge_l5_content,
      $row->field_concierge_l5_icon
    );
    $content .= '</div>';

    $content .= '<div class="span6">';
    $content .= $row->field_concierge_c1_custom;

    $content .= $this->build_card(
      $row->field_concierge_c1_heading,
      $row->field_concierge_c1_content,
      $row->field_concierge_c1_description,
      $row->field_concierge_c1_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c2_heading,
      $row->field_concierge_c2_content,
      $row->field_concierge_c2_description,
      $row->field_concierge_c2_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c3_heading,
      $row->field_concierge_c3_content,
      $row->field_concierge_c3_description,
      $row->field_concierge_c3_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c4_heading,
      $row->field_concierge_c4_content,
      $row->field_concierge_c4_description,
      $row->field_concierge_c4_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c5_heading,
      $row->field_concierge_c5_content,
      $row->field_concierge_c5_description,
      $row->field_concierge_c5_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c6_heading,
      $row->field_concierge_c6_content,
      $row->field_concierge_c6_description,
      $row->field_concierge_c6_image
    );
    $content .= $this->build_card(
      $row->field_concierge_c7_heading,
      $row->field_concierge_c7_content,
      $row->field_concierge_c7_description,
      $row->field_concierge_c7_image
    );
    $content .= '</div>';

    $content .= '<div class="span3">';
    
    $content .= $this->build_side_card(
      $row->field_concierge_r1_heading,
      $row->field_concierge_r1_content,
      $row->field_concierge_r1_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_r2_heading,
      $row->field_concierge_r2_content,
      $row->field_concierge_r2_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_r3_heading,
      $row->field_concierge_r3_content,
      $row->field_concierge_r3_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_r4_heading,
      $row->field_concierge_r4_content,
      $row->field_concierge_r4_icon
    );
    $content .= $this->build_side_card(
      $row->field_concierge_r5_heading,
      $row->field_concierge_r5_content,
      $row->field_concierge_r5_icon
    );
    $content .= '</div>';

    $row->content = $content;
  }

  public function build_side_card($heading = '', $content = '', $icon = '') {
    if (empty($heading)) {
      return '';
    }
    $card = '<div class="box">';
    if (empty($icon)) {
      $card .= '<h2>' . $heading . '</h2>' . "\n";
    }
    else {
      $card .= '<h2 class="' . $icon . '">' . $heading . '</h2>' . "\n";
    }
    if (!empty($content)) {
      $card .= $content;
    }
    $card .= '</div>';
    return $card;
  }

  public function build_card($heading = '', $content = '', $description = '', $image_id = '') {
    if (empty($heading)) {
      return '';
    }
    $card = '<div class="postcard-left box">';
    if ($image_id) {
      $card .= '<div>';
      $real_file_id = $this->handleSourceMigration(array('FileMigration'), array($image_id));
      $file = file_load($real_file_id);
      global $base_url;
      $base_url = 'http://itservices.stanford.edu';
      $img = theme_image(array('path' => $file->uri));
      $card .= $img;
      $card .= '</div>';
    }
    $card .= '<div>';
    if (!empty($heading)) { 
	  $card .= '<h2>' . $heading . '</h2>' . "\n";
    }
    if (!empty($description)) { 
	  $card .= $description . "\n";
    }
    if (!empty($content)) {
	  $card .= $content;
    }
    $card .= '</div>';
    $card .= '</div>';
    return $card;
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
 * Service Page mappings and handling
 */
class d6d7ServiceInformationMigration extends d6d7NodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('uid', 'uid');

    // Create a node with the same ID
    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('is_new')->defaultValue('TRUE');

    // Notice
    $this->addFieldMapping('field_information_notice', 'field_details_notice');
    $this->addFieldMapping('field_information_notice:format')->defaultValue('full_html');
    $this->addFieldMapping('field_information_notice:language')->defaultValue(LANGUAGE_NONE);

    // Internal
    $this->addFieldMapping('field_information_internal', 'field_details_internal');
    $this->addFieldMapping('field_information_internal:format')->defaultValue('full_html');
    $this->addFieldMapping('field_information_internal:language')->defaultValue(LANGUAGE_NONE);

	// Body
    $this->addFieldMapping('body', 'field_details_content');
    $this->addFieldMapping('body:format')->defaultValue('full_html');

	// Services
	$this->addFieldMapping('field_service', 'field_details_services');

    // Files
    $this->addFieldMapping('field_information_files', 'field_details_files')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_information_files:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_information_files:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_information_files:language')->defaultValue(LANGUAGE_NONE);

    // Images
    $this->addFieldMapping('field_information_images', 'field_details_images')->sourceMigration('FileMigration');
    $this->addFieldMapping('field_information_images:alt', 'field_details_images:data')->callbacks(array($this, 'd6d7_get_alt'));;
    $this->addFieldMapping('field_information_images:file_class')->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_information_images:preserve_files')->defaultValue(TRUE);
    $this->addFieldMapping('field_information_images:language')->defaultValue(LANGUAGE_NONE);
  }

  // The value, as passed is an array of serialized arrays, one per image per row
  // We take the array, unserialize each value and extract the alt string and
  // setting that as the value for each array item.

  protected function d6d7_get_alt($data) {

    // This will be an array of alt tags (strings)
    $new_data = array();

    // loop through each value in the data field for the image, in D6, that's a serialized array
	foreach ($data as $key => $value) {
	  $value = unserialize($value);
      if(!empty($value['alt'])) {
        $new_data[$key] = $value['alt'];
      }
      else {
        $new_data[$key] = '';
      }
	}
    return $new_data;
  }

  // modify the source query
  protected function query() {
    $query = parent::query();

    // Only import published nodes
    $query->condition('status', '1', '=');
    return $query;
  }
}

function d6d7_build_expression($title, $first_field, $second_field = '', $heading = 'h3') {
  if ($second_field != '') {
    $sub_expression = "CONCAT_WS('',$first_field, $second_field)";
  }
  else {
    $sub_expression = $first_field;
  }
  $expression = "CONCAT('<$heading>$title</$heading>', IF( length( $sub_expression) , $sub_expression, NULL))";
  return $expression;
}
