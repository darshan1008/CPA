height_t get_height(bst_t* p_bst, data_t data){
	height_t height = 0; 
	bst_node_t* p_run = p_bst->p_root_node; 
	while(p_run != NULL){
		if(p_run->data == data)
			return (height); 
		else {
			++height;
			if(data <= p_run->data) 
				p_run = p_run->left; 
			else
				p_run = p_run->right; 
		}
	}	
	return (-1); 
}