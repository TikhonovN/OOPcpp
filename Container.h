struct ExceptionEmptyContainer {};
struct ExceptionInvalidIndex {
	unsigned int index;
};


template< typename T > class Container {
public:
	Container() {
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}
	~Container() {
		Empty();
	}
	void AddFirst( T const & data ) {
		Node * node = new Node( data );
		if( m_head == nullptr ) {
			m_head = node;
			m_tail = node;
		}
		else {
			node->m_next = m_head;
			m_head->m_prev = node;
			m_head = node;
		}
		++m_size;
	}
	void AddLast( T const & data ) {
		Node * node = new Node( data );
		if( m_tail == nullptr ) {
			m_head = node;
			m_tail = node;
		}
		else {
			node->m_prev = m_tail;
			m_tail->m_next = node;
			m_tail = node;
		}
		++m_size;
	}
	void DeleteFirst() {
		if( m_head == nullptr ) { return; }
		if( m_head == m_tail ) {
			delete m_head;
			m_head = nullptr;
			m_tail = nullptr;
		}
		else {
			Node * temp = m_head;
			m_head = m_head->m_next;
			m_head->m_prev = nullptr;
			delete temp;
		}
		--m_size;
	}
	void DeleteLast() {
		if( m_tail == nullptr ) { return; }
		if( m_head == m_tail ) {
			delete m_tail;
			m_head = nullptr;
			m_tail = nullptr;
		}
		else {
			Node * temp = m_head;
			m_tail = m_tail->m_prev;
			m_tail->m_next = nullptr;
			delete temp;
		}
		--m_size;
	}
	T & GetFirst() {
		if( m_head == nullptr ) {
			ExceptionEmptyContainer exception;
			throw exception;
		}
		return m_head->m_data;
	}
	T & GetLast() {
		if( m_tail == nullptr ) {
			ExceptionEmptyContainer exception;
			throw exception;
		}
		return m_tail->m_data;
	}
	T & operator [] ( unsigned int const index ) {
		if( index > m_size ) {
			ExceptionInvalidIndex exception;
			exception.index = index;
			throw exception;
		}
		Node * temp = m_head;
		for( unsigned int i = 0; i < index; ++i ) {
			temp = temp->m_next;
		}
		return temp->m_data;
	}
	unsigned int GetSize() {
		return m_size;
	}
	bool IsEmpty() {
		if( m_size == 0 ) {
			return true;
		}
		return false;
	}
	void Empty() {
		while( m_size != 0 ) {
			DeleteFirst();
		}
	}
private:
	struct Node {
		Node( T const & data ) {
			m_data = data;
			m_prev = nullptr;
			m_next = nullptr;
		}
		T m_data;
		Node * m_prev, * m_next;
	};
	Node * m_head, * m_tail;
	unsigned int m_size;
};