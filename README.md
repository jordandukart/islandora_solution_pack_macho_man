# Islandora Macho Man Solution Pack

Sample module in order to give you a framework to learn how to query Solr in Islandora, oh yeah!

Based off of the sample module used at Islandora Camp Colorado located [here](https://github.com/daniel-dgi/islandora_solution_pack_meme).

Bootstrapping your VM
---------------------
What good is a tutorial on querying Solr if there’s no content to query?  Follow these steps to give your VM enough data to make this meaningful.

From the admin toolbar, go to Islandora -> Solution pack configuration -> Solution pack required objects.  Scroll down to ‘Islandora Macho Man’ and select the checkbox. Then click the ‘Force reinstall objects’ button.  This will install the collection required for this module.

If you’re curious, feel free to check out the source code in the .module file to see how we’re creating this collection in the islandora_required_objects hook.

Next, download the .zip files from the ‘content’ folder of this module from github. Alternatively, if you’re savvy with the command line, you can scp them over like so:

`scp -P 2222 vagrant@localhost:/var/www/drupal/htdocs/sites/all/modules/islandora_solution_pack_macho_man/content/*.zip .`

Now let’s feed these files to the batch importer.  Navigate to [`localhost:8080/islandora/object/machoman:collection`](localhost:8080/islandora/object/machoman:collection) and click on its 'manage' tab.  Then click on its ‘collection’ tab.  Then click on the ‘Batch imort objects’ link.  Select ‘ZIP File Importer’ from the dropdown, click next, and upload the corresponding machoman.zip file.  Make sure to click the ‘Islandora Basic Image Content model’ checkbox to give each object the content model from the basic image solution pack.

That’s it, you now have plenty of silly objects to work with.  Best of all, because of the FedoraGSearch setup on these VMs, all the metadata from these objects have been automatically indexed in Solr!

Let’s Query Already!
------------
Navigate to [`localhost:8080/devel/php`](localhost:8080/devel/php).  This is allows you to execute PHP code within Drupal. We’re going to use it to run the following code snippets.

Getting Members of a Collection
-------------------------------
```php
$qp = new IslandoraSolrQueryProcessor();
$query = 'RELS_EXT_isMemberOfCollection_uri_ms:"info:fedora/machoman:collection"';
$qp->buildQuery($query);
$qp->executeQuery(FALSE);
dsm($qp, 'query processor');
$results = $qp->islandoraSolrResult['response'];
dsm($results, 'results');
```

This will return all fields present for the objects found by the above query which tends to be a lot.

Limiting returned fields
------------------------
```php
$qp = new IslandoraSolrQueryProcessor();
$query = 'RELS_EXT_isMemberOfCollection_uri_ms:"info:fedora/machoman:collection"';
$qp->buildQuery($query);
$qp->solrParams['fl'] = "PID, fgs_label_s";
$qp->executeQuery(FALSE);
dsm($qp, 'query processor');
$results = $qp->islandoraSolrResult['response'];
dsm($results, 'results');
```

This limits our results to returning just the PID and the label of the object found.

Finding out what’s in your index
--------------------------------
This couldn’t be easier.  Simply pop open a web browser and navigate to Solr’s built in schema browser at [`http://localhost:8080/solr/#/collection1/schema-browser`](http://localhost:8080/solr/#/collection1/schema-browser).  This page will show you everything that’s been indexed.

The field names present are just naming conventions.  Each field is prefixed with the datastream it comes from (e.g. MODS or RELS_EXT).  Each field is also suffixed with letters describing the type of field:  ‘m’ for multivalued, ‘s’ for string, and ‘t’ for text.  These can be concatenated, so you’ll often see ‘ms’ or ‘mt’ on the end of field names.

Querying through the Solr Admin
--------------------------------
Navigate to [`http://localhost:8080/solr/#/collection1/query`](http://localhost:8080/solr/#/collection1/query).

Construct a query `PID:"machoman:1"` and search. What you see is all the fields and their indexed values for the `machoman:1` object.

Refining the Macho Man
---------------------------
The initial query was pretty general which just returned all children of the `machoman:collection`. Let's refine that down to only children that snap into some Slim Jims.

```php
$qp = new IslandoraSolrQueryProcessor();
$query = 'mods_subject_topic_ms:"Slim Jim"';
$qp->buildQuery($query);
$qp->solrParams['fl'] = "PID, fgs_label_s";
$qp->executeQuery(FALSE);
dsm($qp, 'query processor');
$results = $qp->islandoraSolrResult['response'];
dsm($results, 'results');
```

Limiting further
----------------------
Use the 'fq' Solr param to apply a filter query.  Here we limit by objects where the Macho Man has Slim Jims and is nodding in appreciation.

```php
$qp = new IslandoraSolrQueryProcessor();
$query = 'mods_subject_topic_ms:"Slim Jim"';
$qp->buildQuery($query);
$qp->solrParams['fl'] = "PID, fgs_label_s";
$qp->solrParams['fq'] = 'mods_subject_topic_ms:"nodding"';
$qp->executeQuery(FALSE);
dsm($qp, 'query processor');
$results = $qp->islandoraSolrResult['response'];
dsm($results, 'results');
```
Facet queries
----------------------
Facet queries allow us to get counts of different values present per a Solr field.

```php
$qp = new IslandoraSolrQueryProcessor();
$query = '*:*';
$qp->buildQuery($query);
$qp->solrParams['fl'] = "PID, fgs_label_s";
$qp->solrParams['facet.field'] = 'mods_subject_topic_ms';
$qp->executeQuery(FALSE);
dsm($qp, 'query processor');
$facets = $qp->islandoraSolrResult['facet_counts'];
dsm($facets, 'facets');
```
An example of a module that does something similar to this while not using the Query Processor directly (boo), is the [Islandora Solr Facet Pages](https://github.com/Islandora/islandora_solr_facet_pages) module.

Solr Metadata
----------------------
The [Islandora Solr Metadata](https://github.com/Islandora/islandora_solr_metadata) module allows for custom metadata configurations to be driven by Solr on a per content model basis. To do this navigate to [`localhost:8080/admin/islandora/metadata`](localhost:8080/admin/islandora/metadata) and select the Islandora Solr Metadata display radio button and click Save Configuration. NOTE: If the Solr Metadata display configuration is selected and one isn't present for a content model it'll default back to the Dublin Core display.

Now let's setup a configuration for our sample content. Navigate to [`http://localhost:8080/admin/islandora/search/islandora_solr/metadata`](http://localhost:8080/admin/islandora/search/islandora_solr/metadata) and create a new configuration with a name of your liking. Click on your newly created configuration and add the `Islandora Basic Image Content Model (islandora:sp_basic_image)` content model.
Add some fields to the metadata display, the metadata is pretty sparse for the sample objects but `PID` and `mods_subject_topic_ms` will be present. Add the `mods_abstract_ms` field as a Description and Save the configuration.

Navigate to our `machoman:1` object at [`http://localhost:8080/islandora/object/machoman:1`](http://localhost:8080/islandora/object/machoman:1) and you will now see the configuration display that you just created!

Solr Views
----------------------
Another powerful tool that Solr allows to do is construct Solr queries to be used and display their output within a View in Drupal. Included within the Macho Man SP is a small view that only displays the immediate children of the Macho Man collection and displays their thumbnail. Navigate to [`http://localhost:8080/admin/structure/views/view/`](http://localhost:8080/admin/structure/views/view/) and select the `Macho Man` view. From here you can add additional fields to output, change how the output displays, access datastreams from the objects directly etc. [Views PHP](https://www.drupal.org/project/views_php) is a very powerful module that can be used to run arbitrary PHP snippets when rendering, for the sake of this presentation we won't look at it. The view is available at [`http://localhost:8080/macho-man`](http://localhost:8080/macho-man) to see it rendered.

A feature with Solr Views is the ability to retrieve contextual filters from the URLs to construct output dynamic to the page you are current on. An example "Macho Man Contextual" is included within this module. This will provide a block that will only render on pages that are in the "machoman" namespace and display the topics of the current object. To make this display to navigate [`http://localhost:8080/admin/structure/block`](http://localhost:8080/admin/structure/block) and place the "Macho Man Contextual" View into the region of your choice. If you navigate to a machoman object such as [`localhost:8080/islandora/object/machoman:7`](localhost:8080/islandora/object/machoman:7) you'll see it get rendered. NOTE: that it does not show up on any other objects.
