#ifndef NGINE_FIELD_HDR
#define NGINE_FIELD_HDR

#include "NBase.h"

///Stores an internal Array of given Type and Dimensions
template<typename T>
class NField{

private:
	///Array Dimensions
	uint m_width  = 1;
	uint m_height = 1;

	///Internal Data
    T *m_pArray = nullptr;

public:
	///Intitialize encapsulated Array
	NField(void){

		//Initialize the Array w/ one Entry by Default
		m_pArray = new T[1];
	}

	///Intitialize encapsulated Array
	NField(uint w, uint h){

		//Initialize the Array w/ Amount of Entries passed
		m_pArray = new T[w * h];
		m_width  = w;
		m_height = h;
	}

	///Get the underlying Array Entry Count
	uint getEntryCount(void) const{ return m_width * m_height; }

	///Get the Field's Width
	uint getWidth(void) const{ return m_width; }

	///Get the Field's Height
	uint getHeight(void) const{ return m_height; }

    ///Return an Entry's Value
    const T& getEntry(uint x, uint y) const{
		return m_pArray[x + y * m_width];
    }

    ///Set an Entry's Value
    void setEntry(uint x, uint y, const T &value){

        if(x < m_width && y < m_height){
            m_pArray[x + y * m_width] = value;
        }
        else cerr << "Trying to write to Entry {" << x << "|" << y << "} of NField {" << m_width << "|" << m_height << "} - Out of Bounds!" << endl;
    }

	///Resize the Field
	void resize(uint w, uint h){

		m_width  = w;
		m_height = h;

		//Array won't exist afterwards
		if(w == 0 || h == 0){

			if(m_pArray){
				delete[] m_pArray;
				m_pArray = nullptr;
			}
		}

		else if(m_pArray){

			//Copy Entries that will persist
			T *pTemp = new T[w * h];
			for(uint i = 0; i < w * h; ++i){
				pTemp[i] = m_pArray[i];
			}

			//Delete old Array
			delete[] m_pArray;

			//Assign Array to Member
			m_pArray = pTemp;
		}
	}

	///Erase all Field Entries
	void clear(void){

		if(m_pArray){
			delete[] m_pArray;
			m_pArray = new T[m_width * m_height];
		}
	}

	///Free Array Memory
	virtual ~NField(void){

		if(m_pArray){

			delete[] m_pArray;
			m_pArray = nullptr;
		}

		m_width = m_height = 0;
	}
};

#endif // NGINE_FIELD_HDR
