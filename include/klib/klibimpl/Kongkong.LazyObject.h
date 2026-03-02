#ifndef KLIB_KONGKONG_LAZYOBJECT_H
#define KLIB_KONGKONG_LAZYOBJECT_H

#include "base.h"

namespace klib::Kongkong
{
    /// @brief 遅延初期化可能なオブジェクト
    /// @tparam T 格納する型
    template <class T>
    struct LazyObject final {
        public:
        using ElementType = typename ::std::remove_cv_t<T>;
        constexpr bool IsNothrowCopyConstructible = ::std::is_nothrow_copy_constructible_v<ElementType>;
        constexpr bool IsNothrowCopyAssignable = ::std::is_nothrow_copy_assignable_v<ElementType>;
        constexpr bool IsNothrowMoveConstructible = ::std::is_nothrow_move_constructible_v<ElementType>;
        constexpr bool IsNothrowMoveAssignable = ::std::is_nothrow_move_assignable_v<ElementType>;
        private:

        alignas(alignof(ElementType)) byte m_placeHolder[sizeof(ElementType)];
        bool m_isInitialized;

        void do_checkInitialized() const;
        void do_checkNotInitialized() const;

        public:

        /// @brief 値を格納したLazyObjectを作成
        /// @tparam Args 引数テンプレート
        /// @param args Tのコンストラクタ引数
        template <class... Args>
        static LazyObject Make(
            Args&&... args
        ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)));

        /// @brief 値を格納していない状態で作成
        constexpr LazyObject(
        ) noexcept;

        /// @brief 値を格納していない状態で作成
        constexpr LazyObject(
            ::std::nullptr_t
        ) noexcept;

        LazyObject(
            LazyObject const& other
        ) noexcept(IsNothrowCopyConstructible);

        LazyObject(
            LazyObject&& other
        ) noexcept(IsNothrowMoveConstructible);

        ~LazyObject();

        LazyObject& operator=(
            LazyObject const& right
        ) noexcept(IsNothrowCopyAssignable);

        LazyObject& operator=(
            LazyObject&& other
        ) noexcept(IsNothrowMoveAssignable);

        /// @brief 値を格納している場合は破棄
        LazyObject& operator=(
            ::std::nullptr_t
        ) noexcept;

        /// @brief 値のメンバーアクセス
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        ElementType* operator->();

        [[nodiscard]]
        const ElementType* operator->() const;

        /// @brief 値の間接参照
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        ElementType& operator*();

        [[nodiscard]]
        ElementType const& operator*() const;

        /// @brief 値へのポインターを取得
        [[nodiscard]]
        ElementType* GetPointerUnsafe() noexcept;
        
        [[nodiscard]]
        ElementType const* GetPointerUnsafe() const noexcept;

        /// @brief 値の参照を取得
        [[nodiscard]]
        ElementType& GetValueUnsafe() noexcept;
        
        [[nodiscard]]
        ElementType const& GetValueUnsafe() const noexcept;

        /// @brief 値を格納
        /// @tparam Args 引数テンプレート
        /// @param args Tのコンストラクタ引数
        /// @throws InvalidOperationException: このインスタンスがすでに値を持っているとき
        template <class... Args>
        void Initialize(
            Args&&... args
        );

        /// @brief 値を格納
        /// @tparam Args 引数テンプレート
        /// @param args Tのコンストラクタ引数
        template <class... Args>
        void InitializeUnsafe(
            Args&&... args
        ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)));

        /// @brief 値へのポインター
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        ElementType* Pointer();

        /// @brief 値へのポインター
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        const ElementType* Pointer() const;
        
        /// @brief 値の置き換え
        /// @tparam Args 引数テンプレート
        /// @param args Tの代入演算子の引数
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        template <class... Args>
        void Replace(
            Args&&... args
        );

        /// @brief 値の置き換え
        /// @tparam Args 引数テンプレート
        /// @param args Tの代入演算子の引数
        template <class... Args>
        void ReplaceUnsafe(
            Args&&... args
        ) noexcept(
            noexcept(
                ElementType(::std::forward<Args>(args)...)
            )
            && IsNothrowMoveAssignable
        );

        /// @brief 値を破棄
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        void Reset();

        /// @brief 値を破棄
        void ResetUnsafe() noexcept;

        /// @brief 値をセット
        /// @attention すでに値を持っている場合は置き換えるよ！
        /// @tparam Args 引数テンプレート
        /// @param args Tの代入演算子の引数
        template <class... Args>
        void SetValue(
            Args&&... args
        ) noexcept(
            noexcept(
                ElementType(::std::forward<Args>(args)...)
                && IsNothrowMoveAssignable
            )
        );

        [[nodiscard]]
        bool TryGetPointer(
            ElementType*& result
        ) noexcept;

        [[nodiscard]]
        bool TryGetPointer(
            const ElementType*& pointer
        ) noexcept;

        [[nodiscard]]
        bool TryGetPointer(
            const ElementType*& pointer
        ) const noexcept;

        template <class... Args>
        [[nodiscard]]
        bool TryInitialize(
            Args&&... args
        ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)));

        [[nodiscard]]
        bool TryReset() noexcept;

        /// @brief 値の参照
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        ElementType& Value();

        /// @brief 値の参照
        /// @throws InvalidOperationException: このインスタンスが値を持っていないとき
        [[nodiscard]]
        ElementType const& Value() const;
    };

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator==(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept;

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator==(
        LazyObject<T> const& left,
        T const& right
    ) noexcept;

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator==(
        T const& left,
        LazyObject<T> const& right
    ) noexcept;

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator!=(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept;

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator!=(
        LazyObject<T> const& left,
        T const& right
    ) noexcept;

    template <class T> requires ::std::equality_comparable<T>
    [[nodiscard]]
    bool operator!=(
        T const& left,
        LazyObject<T> const& right
    ) noexcept;

    template <class T> requires ::std::totally_ordered<T>
    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept;

    template <class T> requires ::std::totally_ordered<T>
    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        LazyObject<T> const& left,
        T const& right
    ) noexcept;

    template <class T> requires ::std::totally_ordered<T>
    [[nodiscard]]
    ::std::strong_ordering operator<=>(
        T const& left,
        LazyObject<T> const& right
    ) noexcept;
}

namespace klib::Kongkong
{
    template <class T>
    template <class... Args>
    LazyObject<T> LazyObject<T>::Make(
        Args&&... args
    ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)))
    {
        LazyObject<T> obj;
        obj.InitializeUnsafe<Args...>(::std::forward<Args>(args)...);

        return obj;
    }
    
    template <class T>
    constexpr LazyObject<T>::LazyObject() noexcept
        : m_placeHolder{}
        , m_isInitialized(false)
    {
    }

    template <class T>
    constexpr LazyObject<T>::LazyObject(
        ::std::nullptr_t
    ) noexcept
        : LazyObject<T>()
    {
    }

    template <class T>
    LazyObject<T>::LazyObject(
        LazyObject<T> const& other
    ) noexcept(IsNothrowCopyConstructible)
        : LazyObject<T>()
    {
        if (other.m_isInitialized) {
            new (GetPointerUnsafe()) ElementType(other.GetValueUnsafe());
            m_isInitialized = true;
            return;
        }

        m_isInitialized = false;
    }

    template <class T>
    LazyObject<T>::LazyObject(
        LazyObject<T>&& other
    ) noexcept(IsNothrowMoveConstructible)
    {
        if (other.m_isInitialized) {
            new (GetPointerUnsafe()) ElementType(::std::move(other.GetValueUnsafe()));
            this->m_isInitialized = true;
            return;
        }

        this->m_isInitialized = false;
    }

    template <class T>
    LazyObject<T>::~LazyObject()
    {
        if (m_isInitialized) GetValueUnsafe().~ElementType();
    }

    template <class T>
    LazyObject<T>& LazyObject<T>::operator=(
        LazyObject<T> const& other
    ) noexcept(IsNothrowCopyAssignable)
    {
        if (&other != this) [[likely]] {
            if (other.m_isInitialized) {
                SetValue<ElementType const&>(other.GetValueUnsafe());
            }
            else {
                ResetUnsafe();
            }
        }
        
        return *this;
    }

    template <class T>
    LazyObject<T>& LazyObject<T>::operator=(
        LazyObject<T>&& other
    ) noexcept(IsNothrowMoveAssignable)
    {
        if (&other != this) [[likely]] {
            if (other.m_isInitialized) {
                SetValue<ElementType&&>(other.GetValueUnsafe());
            }
            else {
                if (m_isInitialized) {
                    GetValueUnsafe().~ElementType();
                    m_isInitialized = false;
                }
            }
        }
        
        return *this;
    }

    template <class T>
    LazyObject<T>& LazyObject<T>::operator=(
        ::std::nullptr_t
    ) noexcept
    {
        if (m_isInitialized) ResetUnsafe();
        return *this;
    }

    template <class T>
    typename LazyObject<T>::ElementType*
    LazyObject<T>::operator->()
    {
        return Pointer();
    }

    template <class T>
    const typename LazyObject<T>::ElementType*
    LazyObject<T>::operator->() const
    {
        return Pointer();
    }

    template <class T>
    typename LazyObject<T>::ElementType&
    LazyObject<T>::operator*()
    {
        return Value();
    }

    template <class T>
    typename LazyObject<T>::ElementType const&
    LazyObject<T>::operator*() const
    {
        return Value();
    }

    template <class T>
    typename LazyObject<T>::ElementType*
    LazyObject<T>::GetPointerUnsafe() noexcept
    {
        return reinterpret_cast<ElementType*>(m_placeHolder);
    }

    template <class T>
    const typename LazyObject<T>::ElementType*
    LazyObject<T>::GetPointerUnsafe() const noexcept
    {
        return reinterpret_cast<const ElementType*>(m_placeHolder);
    }

    template <class T>
    typename LazyObject<T>::ElementType&
    LazyObject<T>::GetValueUnsafe() noexcept
    {
        return *reinterpret_cast<ElementType*>(m_placeHolder);
    }

    template <class T>
    typename LazyObject<T>::ElementType const&
    LazyObject<T>::GetValueUnsafe() const noexcept
    {
        return *reinterpret_cast<const ElementType*>(m_placeHolder);
    }

    template <class T>
    template <class... Args>
    void LazyObject<T>::Initialize(
        Args&&... args
    )
    {
        do_checkNotInitialized();
        InitializeUnsafe<Args...>(::std::forward<Args>(args)...);
    }

    template <class T>
    template <class... Args>
    void LazyObject<T>::InitializeUnsafe(
        Args&&... args
    ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)))
    {
        new (GetPointerUnsafe()) ElementType(::std::forward<Args>(args)...);
        m_isInitialized = true;
    }

    template <class T>
    typename LazyObject<T>::ElementType*
    LazyObject<T>::Pointer()
    {
        do_checkInitialized();
        return GetPointerUnsafe();
    }

    template <class T>
    const typename LazyObject<T>::ElementType*
    LazyObject<T>::Pointer() const
    {
        do_checkInitialized();
        return GetPointerUnsafe();
    }

    template <class T>
    template <class... Args>
    void LazyObject<T>::Replace(
        Args&&... args
    )
    {
        do_checkNotInitialized();
        InitializeUnsafe<Args...>(::std::forward<Args>(args)...);
    }

    template <class T>
    template <class... Args>
    void LazyObject<T>::ReplaceUnsafe(
        Args&&... args
    ) noexcept(
        noexcept(ElementType(::std::forward<Args>(args)...))
        && IsNothrowMoveAssignable
    )
    {
        if constexpr (
            ::std::is_class_v<ElementType>
            || ::std::is_union_v<ElementType>
        ) {
            GetValueUnsafe().operator=(::std::forward<Args>(args)...);
        }
        else {
            GetValueUnsafe() = ElementType(::std::forward<Args>(args)...);
        }
    }

    template <class T>
    void LazyObject<T>::Reset()
    {
        do_checkInitialized();
        ResetUnsafe();
    }

    template <class T>
    void LazyObject<T>::ResetUnsafe() noexcept
    {
        GetValueUnsafe().~ElementType();
        m_isInitialized = false;
    }

    template <class T>
    template <class... Args>
    void LazyObject<T>::SetValue(
        Args&&... args
    ) noexcept(
        noexcept(
            ElementType(::std::forward<Args>(args)...)
            && IsNothrowMoveAssignable
        )
    )
    {
        if (m_isInitialized) {
            ReplaceUnsafe<Args...>(::std::forward<Args>(args)...);
            return;
        }
        
        InitializeUnsafe<Args...>(::std::forward<Args>(args)...);
    }

    template <class T>
    bool LazyObject<T>::TryGetPointer(
        ElementType*& result
    ) noexcept
    {
        if (this->_isInitialized) {
            result = GetPointerUnsafe();
            return true;
        }

        return false;
    }

    template <class T>
    bool LazyObject<T>::TryGetPointer(
        const ElementType*& result
    ) const noexcept
    {
        if (this->_isInitialized) {
            result = GetPointerUnsafe();
            return true;
        }

        return false;
    }

    template <class T>
    template <class... Args>
    bool LazyObject<T>::TryInitialize(
        Args&&... args
    ) noexcept(noexcept(ElementType(::std::forward<Args>(args)...)))
    {
        if (m_isInitialized) return false;
        
        InitializeUnsafe<Args...>(::std::forward<Args>(args)...);
        return true;
    }

    template <class T>
    bool LazyObject<T>::TryReset() noexcept
    {
        if (m_isInitialized) return false;
        
        ResetUnsafe();
        return true;
    }

    template <class T>
    typename LazyObject<T>::ElementType& LazyObject<T>::Value()
    {
        do_checkInitialized();
        return GetValueUnsafe();
    }

    template <class T>
    const typename LazyObject<T>::ElementType&
    LazyObject<T>::Value() const
    {
        do_checkInitialized();
        return GetValueUnsafe();
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator==(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        if (!left.IsInitialized()) return !right.IsInitialized();

        return left.GetValueUnsafe() == right.GetValueUnsafe();
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator==(
        LazyObject<T> const& left,
        T const& right
    ) noexcept
    {
        if (!left.IsInitialized()) return false;

        return left.GetValueUnsafe() == right;
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator==(
        T const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        return right == left;
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator!=(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        return !(left == right);
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator!=(
        LazyObject<T> const& left,
        T const& right
    ) noexcept
    {
        return !(left == right);
    }

    template <class T> requires ::std::equality_comparable<T>
    bool operator!=(
        T const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        return !(left == right);
    }

    template <class T> requires ::std::totally_ordered<T>
    ::std::strong_ordering operator<=>(
        LazyObject<T> const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        if (!left.IsInitialized()) {
            return right.IsInitialized() ? ::std::strong_ordering::less : ::std::strong_ordering::equal;
        }

        return left.GetValueUnsafe() <=> right.GetValueUnsafe();
    }

    template <class T> requires ::std::totally_ordered<T>
    ::std::strong_ordering operator<=>(
        LazyObject<T> const& left,
        T const& right
    ) noexcept
    {
        if (!left.IsInitialized()) return ::std::strong_ordering::less;

        return left.GetValueUnsafe() <=> right;
    }

    template <class T> requires ::std::totally_ordered<T>
    ::std::strong_ordering operator<=>(
        T const& left,
        LazyObject<T> const& right
    ) noexcept
    {
        if (!right.IsInitialized()) return ::std::strong_ordering::greater;

        return left <=> right.GetValueUnsafe();
    }
}

#endif //!KLIB_KONGKONG_LAZYOBJECT_H