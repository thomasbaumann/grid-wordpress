<?php
/**
 * Created by PhpStorm.
 * User: edward
 * Date: 04.10.15
 * Time: 20:39
 */

namespace grid_plugin;


class reuse_container
{
	function __construct(){
		add_action( 'admin_menu', 'admin_menu' );
	}
	function admin_menu(){
		add_submenu_page( 'tools.php', 'reusable grid container', 'Reusable grid container', 'edit_posts', 'grid_reuse_containers', array( $this, 'reuse_containers' ) );
		add_submenu_page( null, 'edit reuse container', 'edit reuse container', 'edit_posts', 'grid_edit_reuse_container', array( $this, 'edit_reuse_container' ) );
		add_submenu_page( null, 'delete reuse container', 'delete reuse container', 'edit_posts', 'grid_delete_reuse_container', array( $this, 'delete_reuse_container') );
	}
	function reuse_containers() {
		$storage = grid_wp_get_storage();
		global $grid_lib;
		$editor = $grid_lib->getReuseContainerEditor();
		grid_enqueue_editor_files($editor);
		$html = $editor->run( $storage, function( $id ) {
			return add_query_arg( array( 'page' => 'grid_edit_reuse_container', 'containerid' => $id ), admin_url( 'admin.php' ) );
		}, function( $id ) {
			return add_query_arg( array( 'page' => 'grid_delete_reuse_container', 'containerid' => $id, 'noheader' => true ), admin_url( 'admin.php' ) );
		} );
		echo $html;
	}
	function edit_reuse_container() {
		$containerid = intval($_GET['containerid']);

		$storage = grid_wp_get_storage();
		global $grid_lib;
		$editor = $grid_lib->getReuseContainerEditor();
		grid_enqueue_editor_files( $editor );
		grid_wp_load_js();
		$html = $editor->runEditor(
			$storage,
			$containerid,
			add_query_arg( array( 'noheader' => true, 'page' => 'grid_ckeditor_config' ), admin_url( 'admin.php' ) ),
			add_query_arg( array( 'noheader' => true, 'page' => 'grid_ajax' ), admin_url( 'admin.php' ) ),
			get_option( 'grid_debug_mode', false ),
			''
		);
		echo $html;
	}

	function delete_reuse_container() {
		$containerid = intval($_GET['containerid']);

		$storage = grid_wp_get_storage();
		global $grid_lib;
		$editor = $grid_lib->getReuseContainerEditor();
		grid_enqueue_editor_files( $editor );
		$html = $editor->runDelete( $storage, $containerid );
		if ( true === $html ) {
			wp_redirect( add_query_arg( array( 'page' => 'grid_reuse_containers' ), admin_url( 'tools.php' ) ) );
			return;
		}
		echo $html;
	}
}