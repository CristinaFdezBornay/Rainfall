#include <necessary_libs.hpp>

class		N {
	public:
		N( void );
		N( int n ) {
			_nbr = n;
		};
		~N( void );

		setAnnotation(char *annotation) {
			this->_annotation = memcpy(annotation, len(annotation));
		};

		virtual int operator+(N &rhs) {
			return (this->_nb + rhs._nbr)
		}

		virtual int operator-(N &rhs) {
			return (this->_nb + rhs._nbr)
		}

	private:
		int		_nbr;
		char	*_annotation;
}

void	main(int argc, char **argv) {
	if (argc < 2)
		exit(1);

	N	*lol = new N(5);
	N	*lal = new N(6);

	lol->setAnnotation(argv[1]);

	//some weird instruction that access the pointer saved on lal :)

	return;
}
