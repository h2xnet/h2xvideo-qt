#ifndef H2XBASE_H2X_MAP_TABLE__H
#define H2XBASE_H2X_MAP_TABLE__H

#include <map>
#include <string>

#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
 * ClassName: ValueMapTable
 * Desc: ֵӳ����࣬���ü�ֵ�Է�ʽ����ӳ��
 * Author: zfs
 * Date: 2021-06-06 08:41
 */
template<typename keyType, typename valueType>
class H2XBASE_EXPORT ValueMapTable {
public:
    ValueMapTable();
    ~ValueMapTable();

    /*
     * FunctionName: set
     * Desc: ����һ����¼
     * Author: zfs
     * Date: 2021-06-06 09:30
     * @key: ��
     * @value: ����Ӧ��ֵ
     * @replace: ���Ϊtrue�������Ѿ�����ʱ���滻��Ϊfalse,��������ʱֱ�ӷ���false
     */
    bool set(const keyType& key, const valueType& value, bool replace = true);

    /*
     * FunctionName: get
     * Desc: ��ȡ����Ӧ��ֵ
     * Author: zfs
     * Date: 2021-06-06 09:31
     * @value: �����ҵ���ֵ����������ڿ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    bool get(const keyType& key, valueType& value);

    /*
     * FunctionName: remove
     * Desc: ɾ��һ�м�¼
     */
    void remove(const keyType& key);

    bool isEmpty() {
        return list_.empty();
    }

    size_t count() {
        return list_.size();
    }

    void clear() {
        if (!list_.empty()) {
            list_.clear();
        }
    }

private:
    typedef std::map<keyType, valueType> ValueMapType;

    ValueMapType list_;
};

template<typename keyType, typename valueType>
ValueMapTable<keyType, valueType>::ValueMapTable() {

}

template<typename keyType, typename valueType>
ValueMapTable<keyType, valueType>::~ValueMapTable() {
    this->clear();
}

template<typename keyType, typename valueType>
bool ValueMapTable<keyType, valueType>::set(const keyType& key, const valueType& value, bool replace) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        // �滻
        if (replace) {
            memcpy(it->second, value, sizeof(value));
            return true;
        }
        return false;
    }

    // ���
    std::pair<std::map<keyType, valueType>::iterator, bool> result = 
        list_.insert(std::pair<keyType, valueType>(key, value));

    return result.second;
}

template<typename keyType, typename valueType>
bool ValueMapTable<keyType, valueType>::get(const keyType& key, valueType& value) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        //memcpy(&value, it->second, sizeof(value));
        value = it->second;
        return true;
    }
    return false;
}

template<typename keyType, typename valueType>
void ValueMapTable<keyType, valueType>::remove(const keyType& key) {
    std::map<keyType, valueType>::iterator it = list_.find(key);
    if (it != list_.end()) {
        list_.erase(it);
    }
}


///////////////////////////////////////////////////////////////////////////////////
////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////
template<typename keyType>
class H2XBASE_EXPORT PtrMapTable {
public:
    PtrMapTable();
    ~PtrMapTable();

    //
    // set : ���һ����¼�����Ѿ�����ʱ��replace�����Ƿ��滻Ϊ��ֵ
    //
    const void* set(const keyType& key, const void* value, bool replace = true, bool isDelete = true);

    //
    // get : ����һ����¼
    //
    const void* get(const keyType& key);

    //
    // remove : ɾ��һ����¼,isDelete�����Ƿ�Ҫɾ������,true��ִ��delteɾ��������ɾ��
    //
    bool remove(const keyType& key, bool isDelete = true);

    bool isEmpty() {
        return list_.empty();
    }

    size_t count() {
        return list_.size();
    }

private:
    typedef std::map<keyType, const void*> PtrMapType;

    PtrMapType list_;
};

template<typename keyType>
PtrMapTable<keyType>::PtrMapTable() {

}

template<typename keyType>
PtrMapTable<keyType>::~PtrMapTable() {

}

template<typename keyType>
const void* PtrMapTable<keyType>::set(const keyType& key, const void* value, bool replace, bool isDelete) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        if (!replace) {
            return false;
        }
        if (it->second && isDelete) {
            delete it->second;
        }

        it->second = value;

        return value;
    }

    std::pair<std::map<keyType, const void*>::iterator, bool>
        result = list_.insert(std::pair<keyType, const void*>(key, value));

    if (!result.second) {
        return NULL;
    }

    return value;
}

template<typename keyType>
const void* PtrMapTable<keyType>::get(const keyType& key) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        return it->second;
    }
    return NULL;
}

template<typename keyType>
bool PtrMapTable<keyType>::remove(const keyType& key, bool isDelete) {
    std::map<keyType, const void*>::iterator it = list_.find(key);
    if (it != list_.end()) {
        if (it->second && isDelete) {
            delete it->second;
        }
        list_.erase(it);
        return true;
    }
    return false;
}

} // end namespace h2x

#endif // !H2XBASE_H2X_MAP_TABLE__H
