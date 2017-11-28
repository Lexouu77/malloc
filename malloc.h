typedef enum		e_m_type
{
	TINY, SMALL, LARGE
}					t_m_type;

typedef struct		s_page
{
	size_t			size;
	size_t			is_available;
	struct s_page	*next; 
}					t_page

/*
**
** >s_page_ptr<[size][is_available][next]..data
*/

// TODO: check address de s_page et de size

typedef struct		s_m_zone
{
	size_t			size;
	size_t			used_size;
	struct s_page	*next
}					t_m_zone;