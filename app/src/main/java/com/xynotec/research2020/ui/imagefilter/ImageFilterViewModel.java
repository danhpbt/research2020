package com.xynotec.research2020.ui.imagefilter;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import androidx.databinding.ObservableBoolean;
import androidx.databinding.ObservableField;

import com.xynotec.dagger.BaseViewModel;
import com.xynotec.image.ImageUtil;
import com.xynotec.research2020.R;
import com.xynotec.research2020.data.DataManager;

import java.util.concurrent.Callable;

import io.reactivex.Completable;
import io.reactivex.Single;
import io.reactivex.SingleEmitter;
import io.reactivex.SingleOnSubscribe;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.functions.BiConsumer;
import io.reactivex.functions.Consumer;
import io.reactivex.schedulers.Schedulers;

public class ImageFilterViewModel extends BaseViewModel {
    private final ObservableField<Bitmap> mBitmap = new ObservableField<>();
    private int[] mData;
    private int mWidth;
    private int mHeight;

    private final ObservableBoolean mIsLoading = new ObservableBoolean();

    ImageFilterViewModelListener mListener;

    Context context;
    public ImageFilterViewModel(DataManager dataManager) {
        super(dataManager);
        context = getDataManager().getContext();

        reload();
    }

    public ObservableBoolean getIsLoading() {
        return mIsLoading;
    }

    public void setIsLoading(boolean isLoading) {
        mIsLoading.set(isLoading);
    }

    public ObservableField<Bitmap> getBitmap()
    {
        return mBitmap;
    }

    public void setListener(ImageFilterViewModelListener listener)
    {
        this.mListener = listener;
    }

    public void reload()
    {
        setIsLoading(true);

        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.effect);
        Bitmap bmpARGB = bitmap.copy(Bitmap.Config.ARGB_8888, true);

        mWidth = bmpARGB.getWidth();
        mHeight = bmpARGB.getHeight();
        mData = new int[mWidth*mHeight];
        bmpARGB.getPixels(mData, 0, mWidth, 0, 0, mWidth, mHeight);

        mBitmap.set(bitmap.copy(Bitmap.Config.ARGB_8888, true));

        bitmap.recycle();
        bmpARGB.recycle();

        setIsLoading(false);
    }

    public void antiGrain()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.AntiGrain(data, mWidth, mHeight);
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void grayScale()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.GrayScale(data, mWidth, mHeight);
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void colorFilter()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.ColorFilter(data, mWidth, mHeight, 0); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void gamma()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Gamma(data, mWidth, mHeight, 0.5, 0.5, 0.5);//value 0->1
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void brightness()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Brightness(data, mWidth, mHeight, -100); //value -255->255
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void contrast()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Contrast(data, mWidth, mHeight, -50); //value -100->100
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void invert()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Invert(data, mWidth, mHeight); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void smooth()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Smooth(data, mWidth, mHeight, 1); //default to 1
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void gaussianBlur()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.GaussianBlur(data, mWidth, mHeight, 20); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void meanRemoval()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.MeanRemoval(data, mWidth, mHeight, 9); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void sharpen()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Sharpen(data, mWidth, mHeight, 11); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void embossLaplacian()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.EmbossLaplacian(data, mWidth, mHeight); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void edgeDetect()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.EdgeDetectQuick(data, mWidth, mHeight); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void flip()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Flip(data, mWidth, mHeight, true, true); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void randomJitter()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.RandomJitter(data, mWidth, mHeight, (short)5); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void swirl()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Swirl(data, mWidth, mHeight, 0.4, true); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void sphere()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Sphere(data, mWidth, mHeight, false); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void timeWarp()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.TimeWarp(data, mWidth, mHeight, (byte)15, false); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void moire()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Moire(data, mWidth, mHeight, 3); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void water()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Water(data, mWidth, mHeight, (short)15, false); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void pixelate()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.Pixelate(data, mWidth, mHeight, (short)15, false); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

    public void fishEye()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.FishEye(data, mWidth, mHeight, 0.03, false, false); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
                .doOnSubscribe(disposable -> {
                    time[0] = System.currentTimeMillis();
                    setIsLoading(true);})
                .doOnTerminate(() -> {
                    time[0] = System.currentTimeMillis() - time[0];
                    setIsLoading(false);})
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(o -> {
                            mBitmap.set((Bitmap)o);
                            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
                            if (mListener != null)
                                mListener.onMessage(msg);
                        },
                        throwable ->{
                        }));
    }

//void LiquidRender(byte* surface);
//void Agg2DOverlayImage(System::Drawing::Bitmap^ overlayImg);
    public void bokehEffects()
    {
        final long[] time = {0};
        getCompositeDisposable().add(Single.create(emitter -> {
            int length = mData.length;
            int[] data = new int[length];

            System.arraycopy(mData, 0, data, 0, length);
            ImageUtil.BokehEffects(data, mWidth, mHeight); //
            Bitmap bitmap = Bitmap.createBitmap(data, 0, mWidth, mWidth, mHeight, Bitmap.Config.ARGB_8888);

            emitter.onSuccess(bitmap);
        })
        .doOnSubscribe(disposable -> {
            time[0] = System.currentTimeMillis();
            setIsLoading(true);})
        .doOnTerminate(() -> {
            time[0] = System.currentTimeMillis() - time[0];
            setIsLoading(false);})
        .subscribeOn(Schedulers.io())
        .observeOn(AndroidSchedulers.mainThread())
        .subscribe(o -> {
            mBitmap.set((Bitmap)o);
            String msg = String.format("ColorFilter image %dx%d in %d", mWidth, mHeight, time[0]);
            if (mListener != null)
                mListener.onMessage(msg);
            },
                throwable ->{
                }));
    }


    interface ImageFilterViewModelListener{
        void onMessage(String msg);
    }
}
